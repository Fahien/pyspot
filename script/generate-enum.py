"""This script reads a json file describing a basic component
to generate the relative pyspot type"""

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


def pyspot_for_type(type):
	if is_builtin_type(type): return type
	if type == 'string'     : return 'pyspot::String'
	else                    : return '%s' % (type)


def initializer_for_type(type, default=None):
	if type == 'int'     : return default if default else '0'
	if type == 'unsigned': return default if default else '0'
	if type == 'float'   : return default if default else '0.0f'
	if type == 'string'  : return 'PyUnicode_FromString("%s")' % (default if default else "")
	else                 : return '%s{%s}.GetIncref()' % (type, default if default else "")


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


def main():
	"""Entry point"""
	if len(sys.argv) < 3:
		exit('Usage: %s <extension name> <enum.json> [-h]' % sys.argv[0])

	# Get the extension name
	extension_name = sys.argv[1]

	# Get the enum path
	enum = sys.argv[2]

	# Read the json file with
	try:
		with open(enum) as json_data:
			data = json.load(json_data)
	except FileNotFoundError:
		exit('Cannot generate PySpot enum: %s not found' % enum)

	# Open jinja template
	template_name = 'Enum.template.h'
	try:
		with open(template_name) as template_file:
			template = Template(template_file.read())
	except FileNotFoundError:
		exit('Cannot render template: %s not found' % template_name)

	# Fill dictionary
	dictionary = {
		'extension': extension_name.lower(),
		'Extension': extension_name.lower().capitalize(),
		'EXTENSION': extension_name.upper(),
		'enum'     : data['name'].lower(),
		'Enum'     : data['name'].lower().capitalize(),
		'ENUM'     : data['name'].upper(),
		'namespace': data['namespace'].lower(),
		'values'   : data['values']
	}

	# Generate the code
	print(template.render(dictionary))


main()
