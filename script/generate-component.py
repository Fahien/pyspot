"""This script reads a json file describing a basic component
to generate the relative pyspot type"""

import sys
import json


def is_builtin_type(type):
	if (type == 'int'      or
	    type == 'unsigned' or
	    type == 'float')  : return True
	else                  : return False


def c_for_type(type):
	if type == 'string': return 'char %s[64]'
	else               : return type + ' %s'


def pyspot_for_type(type):
	if is_builtin_type(type): return type
	if type == 'string'     : return 'pst::String'
	else                    : return 'pst::component::%s' % type


def initializer_for_type(type, default=None):
	if type == 'int'     : return default if default else '0'
	if type == 'unsigned': return default if default else '0'
	if type == 'float'   : return default if default else '0.0f'
	if type == 'string'  : return 'PyUnicode_FromString("%s")' % (default if default else "")
	else                 : return 'pst::component::%s{%s}.GetIncref()'   % (type, default if default else "")


def parser_for_type(type):
	if type == 'int'     : return 'i'
	if type == 'unsigned': return 'I'
	if type == 'float'   : return 'f'
	else                 : return 'O'


def pytype_for_type(type):
	if type == 'short'         : return 'T_SHORT'
	if type == 'int'           : return 'T_INT'
	if type == 'unsigned'      : return 'T_UINT'
	if type == 'long'          : return 'T_LONG'
	if type == 'float'         : return 'T_FLOAT'
	if type == 'double'        : return 'T_DOUBLE'
	if type == 'string'        : return 'T_STRING'
	if type == 'object'        : return 'T_OBJECT'
	if type == 'char'          : return 'T_CHAR'
	if type == 'byte'          : return 'T_BYTE'
	if type == 'ubyte'         : return 'T_UBYTE'
	if type == 'unsigned short': return 'T_USHORT'
	if type == 'unsigned int'  : return 'T_UINT'
	if type == 'unsigned long' : return 'T_ULONG'
	else                       : return 'T_OBJECT_EX'


def create_constructor(name, members):
	"""Creates the constructor"""

	print("\nstatic PyObject* %s_New(PyTypeObject* type, PyObject* args, PyObject* kwds)\n{" % name)
	print('\n%s* self{ reinterpret_cast<%s*>(type->tp_alloc(type, 0)) };\n' % (name, name))
	print("\tif (self != nullptr)\n\t{")
	for member in members:
		default = member['default'] if 'default' in member else None
		print("\t\tself->%s = %s;" % (member['name'], initializer_for_type(member['type'], default)))
		# Check non builtin types
		if not is_builtin_type(member['type']):
			print('\t\tif (self->%s == nullptr)\n\t\t{' % member['name'])
			print('\t\t\tPy_DECREF(self);')
			print('\t\t\treturn nullptr;\n\t\t}')
	print('\t}\n')
	print('\treturn reinterpret_cast<PyObject*>(self);\n}\n')


def create_destructor(name, members):
	"""Creates the destructor"""

	print('\nstatic void %s_Dealloc(%s* self)\n{' % (name, name))
	# DECREF non builtin types
	for member in members:
		if not is_builtin_type(member['type']):
			print('\tPy_XDECREF(self->%s);' % member['name'])
	print('\tPy_TYPE(self)->tp_free(static_cast<PyObject*>(static_cast<void*>(self)));\n}\n')


def create_initializer(name, members):
	"""Creates the initializer function"""

	print('\nstatic int {0}_Init({0}* self, PyObject* args, PyObject* kwds)\n{{'.format(name))

	# Pointers to members of non builtin types
	temp_obj_created = False
	for member in members:
		if not is_builtin_type(member['type']):
			if not temp_obj_created:
				print('\tPyObject* temp{ nullptr };')
				temp_obj_created = True
			print('\tPyObject* %s{ nullptr };' % member['name'])

	# Keyword list
	print('\n\tstatic char* kwlist[]{ ', end='')
	for member in members:
		print('"%s", ' % member['name'], end='')
	print('nullptr };')

	# Parsing string
	print('\tstatic char* fmt{ "|', end='')
	for member in members:
		print('%s' % parser_for_type(member['type']), end='')
	print('" };')

	# Call parse function
	print('\n\tif (!PyArg_ParseTupleAndKeywords(args, kwds, fmt, kwlist', end='')
	for member in members:
		print(', &', end='')
		if is_builtin_type(member['type']):
			print('self->', end='')
		print('%s' % member['name'], end='')
	print('))\n\t{\n\t\treturn -1;\n\t}\n')
	
	# Check non built-in members
	for member in members:
		if not is_builtin_type(member['type']):
			print('\tif (%s)\n\t{' % member['name'])
			print('\t\ttemp = self->%s;' % member['name'])
			print('\t\tPy_INCREF(%s);' % member['name'])
			print('\t\tself->{0} = {0};'.format(member['name']))
			print('\t\tPy_XDECREF(temp);\n\t}\n')
	
	print('\treturn 0;\n}\n')


def create_getter(name, member):
	"""Creates the Python getter"""

	print('\nstatic PyObject* {0}_Get{1}({0}* self, void* closure)\n{{'.format(name, member['name'].capitalize()))
	print('\tPy_INCREF(self->%s);' % member['name'])
	print('\treturn self->%s;' % member['name'])
	print('}\n')


def create_setter(name, member):
	"""Creates the Python setter"""

	# Check value
	print('\nstatic int {0}_Set{1}({0}* self, PyObject* value, void* closure)\n{{'.format(name, member['name'].capitalize()))
	print('\tif (value == nullptr)\n\t{')
	print('\t\tPyErr_SetString(PyExc_TypeError, "Cannot delete the %s attribute");' % member['name'])
	print('\t\treturn -1;\n\t}\n')

	# String check
	if member['type'] == 'string':
		print('\tif (!PyUnicode_Check(value))\n\t{')
		print('\t\tPyErr_SetString(PyExc_TypeError, "The %s attribute value must be a string");' % member['name'])
		print('\t\treturn -1;\n\t}\n')

	print('\tPy_DECREF(self->%s);' % member['name'])
	print('\tPy_INCREF(value);')
	print('\tself->%s = value;\n' % member['name'])
	print('\treturn 0;\n}\n')


def create_members(name, members):
	"""Creates the members array, getters and setters"""

	print('\nstatic PyMemberDef %s_members[]\n{' % name)
	for member in members:
		if is_builtin_type(member['type']):
			print('\t{{ "{0}", {1}, offsetof({2}, {0}), 0, "{0}" }},'.format(member['name'], pytype_for_type(member['type']), name))
	print('\t{ nullptr } // Sentinel\n};\n')


def create_accessors(name, members):
	for member in members:
		if not is_builtin_type(member['type']):
			create_getter(name, member)
			create_setter(name, member)

	print('\nstatic PyGetSetDef %s_accessors[]\n{' % name)
	# Create a
	for member in members:
		if not is_builtin_type(member['type']):
			print('\t{{ "{1}", (getter){0}_Get{2}, (setter){0}_Set{2}, "{2}", nullptr }},'.format(name, member['name'], member['name'].capitalize()))
	print('\t{ nullptr } // Sentinel\n};\n')


def create_object(name):
	"""Create the PyTypeObject"""

	print('\nstatic PyTypeObject %s = {' % (name.lower()))
	# Name
	print('\tPyVarObject_HEAD_INIT(NULL, 0) "pyspot.%s",' % name[6:])
	# Basic size
	print('\tsizeof(%s),' % name)
	# Item size
	print('\t0,')
	# Dealloc
	print('\t(destructor)%s_Dealloc,' % name)
	# Print
	print('\t0,')
	# Getattr
	print('\t0,')
	# Setattr
	print('\t0,')
	# Reserver
	print('\t0,')
	# Repre
	print('\t0,')
	# As number
	print('\t0,')
	# As sequence
	print('\t0,')
	# As mapping
	print('\t0,')
	# Hash
	print('\t0,')
	# Call
	print('\t0,')
	# Str
	print('\t0,')
	# Get Attr
	print('\t0,')
	# Set Attr
	print('\t0,')
	# As buffer
	print('\t0,')
	# Flags
	print('\tPy_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,')
	# Doc
	print('\t"%s object",' % name)
	# Traverse
	print('\t0,')
	# Clear
	print('\t0,')
	# Rich compare
	print('\t0,')
	# Weak list offset
	print('\t0,')
	# Iter
	print('\t0,')
	# Iter next
	print('\t0,')
	# Methods
	print('\t0,')
	# Members
	print('\t%s_members,' % name)
	# Getset
	print('\t%s_accessors,' % name)
	# Base
	print('\t0,')
	# Dict
	print('\t0,')
	# Descr get
	print('\t0,')
	# Descr set
	print('\t0,')
	# Dict offset
	print('\t0,')
	# Init
	print('\t(initproc)%s_Init,' % name)
	# Alloc
	print('\t0,')
	# New
	print('\t%s_New,' % name)
	print('};\n')


def create_wrapper(name, members):
	"""Create a wrapper for the component"""

	print('\nnamespace pyspot\n{\n\nnamespace component\n{\n')
	print('\nclass %s : public pst::Object\n{\npublic:' % name)
	print('\t%s(PyObject* object)\n\t:\tpst::Object{ object }\n\t{}\n' % name)
	print('\t{0}()'.format(name))
	print('\t:	pst::Object\n\t\t{')
	print('\t\t\t(PyType_Ready(&pyspot{1}), PySpot{0}_New(&pyspot{1}, nullptr, nullptr))\n\t\t}}\n\t{{}}\n'.format(name, name[0].lower() + name[1:]))
	arguments = ''
	for member in members:
		if is_builtin_type(member['type']):
			type = c_for_type(member['type'])
		else:
			type = 'pst::Object& %s'
		arguments += '%s, ' % type % member['name']
	arguments = arguments[:-2]
	print('\t{0}({1})'.format(name, arguments))
	print('\t:	pst::Object\n\t\t{')
	print('\t\t\t(PyType_Ready(&pyspot{1}), PySpot{0}_New(&pyspot{1}, nullptr, nullptr))\n\t\t}}\n\t{{'.format(name, name[0].lower() + name[1:]))
	print('\t\tpst::Tuple arguments{ %s };' % len(members))
	for i in range(0, len(members)):
		print('\t\targuments.SetItem(%s, %s);' % (i, members[i]['name']))
	print('\t\tPySpot%s_Init(GetComponent(), arguments.GetObject(), nullptr);' % name)
	print('\t}\n')
	print('\t~%s(){}\n' % name)
	print('\tPySpot{0}* GetComponent()\n\t{{\n\t\treturn reinterpret_cast<PySpot{0}*>(GetObject());\n\t}}'.format(name))

	for member in members:
		type = pyspot_for_type(member['type'])
		print('\n\t%s Get%s()\n\t{' % (type, member['name'].capitalize()))
		if is_builtin_type(member['type']):
			print('\t\treturn GetComponent()->%s;\n\t}\n' % member['name'])
		else:
			print('\t\treturn %s{ PySpot%s_Get%s(GetComponent(), nullptr) };\n\t}\n' % (type, name, member['name'].capitalize()))

	print('};\n')
	print('}\n\n}\n')


def create_struct(includes, wrapper_name, members):
	"""Creates the struct and all the Python functions"""

	name = "PySpot" + wrapper_name
	# Name of the component
	print('#ifndef PST_%s_H' % name.upper())
	print('#define PST_%s_H\n' % name.upper())
	print('#include <cstring>')

	for include in includes:
		print('#include "%s.h"' % include)

	print('#include "pyspot/Interpreter.h"')
	print('#include <structmember.h>')
	print('#include "pyspot/String.h"')
	print('#include "pyspot/Tuple.h"\n')
	print('namespace pst = pyspot;\n')
	print('struct %s\n{' % name)
	print('\tPyObject_HEAD')

	# Members name and type
	for member in members:
		if is_builtin_type(member['type']):
			type = c_for_type(member['type'])
		else:
			type = 'PyObject* %s'
		print('\t%s;' % type % member['name'])

	print('};\n')

	# Create the Python functions
	create_constructor(name, members)
	create_destructor(name, members)
	create_initializer(name, members)
	create_members(name, members)
	create_accessors(name, members)
	create_object(name)
	create_wrapper(wrapper_name, members)

	print('\n#endif // PST_%s_H' % name.upper())


def main():
	"""Entry point"""

	if len(sys.argv) < 2:
		exit('Usage: %s component.json' % sys.argv[0])

	# Get the command line argument
	component = sys.argv[1]


	# Read the json file with
	try:
		with open(component) as json_data:
			data = json.load(json_data)
	except FileNotFoundError:
		exit('Error: %s not found' % component)

	# Write the source code on the standard output
	includes, name, members = data['includes'], data['name'], data['members']
	create_struct(includes, name, members)


main()
