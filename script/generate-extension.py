"""This script generates the PySpotExtension header"""

import sys
import json
from string import Template

PYINIT_FUNC_NAME = 'PyInit_PySpot'

DICTIONARY = {
	'PYINIT_FUNC_NAME': PYINIT_FUNC_NAME
}

def prepare_header(name):
	"""Prepares dictionary template for the header"""
	
	DICTIONARY['extension'] = name.lower()
	DICTIONARY['Extension'] = name.capitalize()
	DICTIONARY['EXTENSION'] = name.upper()

def prepare_source(name, methods, components):
	"""Prepares dictionary template for the source"""

	# Useful stuff
	prepare_header(name)

	# Methods
	list_methods = ""
	for method in methods:
		list_methods += '\t{{ "{0}", {0}, METH_VARARGS, "{1}" }},\n'.format(method['name'], method['description'])
	list_methods += '\t{ nullptr, nullptr, 0, nullptr } // Sentinel'
	DICTIONARY['list_methods'] = list_methods

	# Include components
	include_components = ""
	for component in components:
		include_components += '#include "%s/component/%s.h"\n' % (DICTIONARY['extension'], component)
	DICTIONARY['include_components'] = include_components

	# Add components
	add_components = ""
	for component in components:
		component_var = component.lower()
		add_components += '\tif (PyType_Ready(&pyspot%s) < 0)\n\t{\n\t\treturn nullptr;\n\t}\n' % component_var
		add_components += '\tPy_INCREF(&pyspot%s);\n' % component_var
		add_components += '\tPyModule_AddObject(module, "{0}", reinterpret_cast<PyObject*>(&pyspot{1}));'.format(component, component_var)
	DICTIONARY['add_components'] = add_components

def create_header():
	"""Creates the Extension header"""

	header_file = open('Extension.template.h')
	header_temp = Template(header_file.read())
	print(header_temp.substitute(DICTIONARY))


def create_source():
	"""Creates the Extension source"""

	source_file = open('Extension.template.cpp')
	source_temp = Template(source_file.read())
	print(source_temp.substitute(DICTIONARY))


def main():
	"""Entry point"""

	if len(sys.argv) < 2:
		exit('Usage: %s extension.json [-h]' % sys.argv[0])

	# Get the json path
	extension = sys.argv[1]

	# Read the json file
	try:
		with open(extension) as json_data:
			data = json.load(json_data)
	except FileNotFoundError:
		exit('Cannot generate PySpot extension: %s not found' % extension)

	name = data['name']

	# Check the header switch
	if len(sys.argv) == 3 and sys.argv[2] == '-h':
		prepare_header(name)
		create_header()
	else:
		methods    = data['methods']
		components = data['components']
		prepare_source(name, methods, components)
		create_source()


main()
