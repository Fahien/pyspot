"""This script reads a json file describing a basic component
to generate the relative pyspot type"""

import os
import sys
import json
from jinja2 import Template


def is_builtin_type(type):
	if (type == 'int'      or
	    type == 'unsigned' or
	    type == 'float')  : return True
	else                  : return False


def c_for_type(type):
	if type == 'string': return 'char %s[64]'
	else               : return type + ' %s'


def to_python_type(type):
	if type == 'int'    : return 'PyLong_FromLong(static_cast<long>(%s))'
	if type == 'long'   : return 'PyLong_FromLong(%s)'
	if type == 'float'  : return 'PyFloat_FromDouble(static_cast<double>(%s))'
	if type == 'double' : return 'PyFloat_FromDouble(%s)'
	if type == 'cstring': return 'PyUnicode_FromString(%s)'
	if type == 'string' : return 'PyUnicode_FromString(%s.c_str())'
	else                : return 'pyspot::Wrapper<'+type+'>{ %s }.GetIncref()'


def to_c_type(type):
	if type == 'int'    : return 'static_cast<int>(PyLong_AsLong(%s))'
	if type == 'long'   : return 'PyLong_AsLong(%s)'
	if type == 'float'  : return 'static_cast<float>(PyFloat_AsDouble(%s))'
	if type == 'double' : return 'PyFloat_AsDouble(%s)'
	if type == 'cstring': return 'PyUnicode_AsUTF8(%s)'
	if type == 'string' : return 'PyUnicode_AsUTF8(%s)'
	else                : return '*reinterpret_cast<'+type+'*>(reinterpret_cast<_PyspotWrapper*>(%s)->data)'


def pyspot_for_type(extension, type):
	if type == 'float' : return 'pyspot::Float'
	if type == 'string': return 'pyspot::String'
	else               : return '%s::%s' % (extension, type)


def initializer_for_type(extension, type, default=None):
	if type == 'int'     : return default if default else '0'
	if type == 'unsigned': return default if default else '0'
	if type == 'float'   : return default if default else '0.0f'
	if type == 'string'  : return 'PyUnicode_FromString("%s")' % (default if default else "")
	else                 : return '%s::%s{%s}.GetIncref()' % (extension, type, default if default else "")


def parser_for_type(type):
	if type == 'int'     : return 'i'
	if type == 'long'    : return 'l'
	if type == 'unsigned': return 'I'
	if type == 'float'   : return 'f'
	if type == 'double'  : return 'd'
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


def method_flags_for_args(args):
	return 'METH_VARARGS | METH_KEYWORDS'
	if len(args) == 0: return 'METH_NOARGS'
	if len(args) == 1: return 'METH_O'
	else             : return 'METH_VARARGS | METH_KEYWORDS'


def load_include(namespace_path, type_name):
	"""Loads a json type"""
	extension_path = os.path.dirname(namespace_path)

	type_path = '%s/%s.json' % (namespace_path, type_name)
	if not os.path.exists(type_path):
		type_path = '%s/%s.json' % (extension_path, type_name.replace('::', '/'))
		if not os.path.exists(type_path):
			raise FileNotFoundError('Cannot load type: %s not found' % type_path)

	with open(type_path) as type_file:
		return json.load(type_file)


def main():
	"""Entry point"""
	if len(sys.argv) < 4:
		exit('Usage: %s <python version> <extension name> <component.json> [<output path>]' % sys.argv[0])
	
	# Get python version
	python_version = sys.argv[1]

	# Get the extension name
	extension_name = sys.argv[2]

	# Get the component path
	component_path = sys.argv[3]

	# Read the json file with
	try:
		with open(component_path) as json_data:
			data = json.load(json_data)
	except FileNotFoundError:
		exit('Cannot generate PySpot component: %s not found' % component_path)

	# Open jinja template
	template_name = python_version + '/Component.template.h'
	try:
		with open(template_name) as template_file:
			template = Template(template_file.read(), extensions=['jinja2.ext.loopcontrols'])
	except FileNotFoundError:
		exit('Cannot render template: %s not found' % template_name)

	# Load members, enum values, and methods
	members = data['members'] if 'members' in data else []
	values  = data['values']  if 'values'  in data else []
	methods = data['methods'] if 'methods' in data else []

	# Load includes
	namespace_path = os.path.dirname(component_path)
	includes = []
	types_loaded = []
	for member in members:
		if (not member['type'] in types_loaded  and
		    not is_builtin_type(member['type']) and
		    member['type'] != 'string'          and
		    member['type'] != 'cstring'):
			includes.append(load_include(namespace_path, member['type']))
			types_loaded.append(member['type'])

	# Fill dictionary
	dictionary = {
		'extension': extension_name.lower(),
		'Extension': extension_name.lower().capitalize(),
		'EXTENSION': extension_name.upper(),
		'namespace': data['namespace'],
		'includes' : includes,
		'component': data['name'].lower(),
		'Component': data['name'].lower().capitalize(),
		'COMPONENT': data['name'].upper(),
		'members'  : members,
		'values'   : values,
		'methods'  : methods
	}

	# Generate the code
	code = template.render(dictionary,
		initializer_for_type=initializer_for_type,
		is_builtin_type=is_builtin_type,
		parser_for_type=parser_for_type,
		pytype_for_type=pytype_for_type,
		to_python_type=to_python_type,
		to_c_type=to_c_type,
		pyspot_for_type=pyspot_for_type,
		c_for_type=c_for_type,
		method_flags_for_args=method_flags_for_args)

	# Output
	if len(sys.argv) == 5:
		# Write code to file
		file_path = sys.argv[4]
		parent_path = os.path.dirname(file_path)
		if not os.path.exists(parent_path):
			os.makedirs(parent_path)
		with open(file_path, "w") as out:
			out.write(code)
	else:
		# Write to std output
		print(code)

main()
