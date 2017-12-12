"""This script generates the PySpotExtension header"""

import sys
import json

PYINIT_FUNC_NAME = 'PyInit_PySpot'


def create_header(name):
	"""Creates the Extension header"""

	print('#ifndef PST_{0}_H\n#define PST_{0}_H\n'.format(name.upper()))

	print('#include "PySpot.h"\n')
	print('PyMODINIT_FUNC %s();\n' % PYINIT_FUNC_NAME)
	print('#endif // PST_%s_H' % name.upper())


def create_source(name, components):
	"""Creates the Extension source"""

	# Name of the component
	print('#include "%s.h"' % name)
	for component in components:
		print('#include "%s.h"' % component)
	print('\n#define GETSTATE(m) (reinterpret_cast<ModuleState*>(PyModule_GetState(m)))\n')
	print('static PyObject* pstError;\n')
	print('struct ModuleState\n{\n\tPyObject* error;\n};\n')
	print('static struct PyModuleDef moduleDef\n{')
	print('\tPyModuleDef_HEAD_INIT,')
	print('\t"pyspot",')
	print('\tnullptr,')
	print('\tsizeof ModuleState,')
	print('\tnullptr,')
	print('\tnullptr,')
	print('\tnullptr,')
	print('\tnullptr,')
	print('\tnullptr,')
	print('};\n')

	print('\nPyMODINIT_FUNC %s()\n{' % PYINIT_FUNC_NAME)
	print('\t// Create the module')
	print('\tPyObject* module{ PyModule_Create(&moduleDef) };')
	print('\tif (module == nullptr)\n\t{\n\t\treturn nullptr;\n\t}\n')

	print('\t// Module exception')
	print('\tpstError = PyErr_NewException("pyspot.error", nullptr, nullptr);')
	print('\tPy_INCREF(pstError);')
	print('\tPyModule_AddObject(module, "error", pstError);\n')

	# Components
	for component in components:
		component = component[0].lower() + component[1:]
		print('\tif (PyType_Ready(&%s) < 0)\n\t{\n\t\treturn nullptr;\n\t}' % component)
		print('\tPy_INCREF(&%s);' % component)
		print('\tPyModule_AddObject(module, "{0}", reinterpret_cast<PyObject*>(&{1}));\n'.format(component.capitalize(), component))

	print('\treturn module;\n};')


def main():
	"""Entry point"""

	if len(sys.argv) < 2:
		exit('Usage:\n\t{0} <list of components>\n\t{0} -h' % sys.argv[0])

	name = 'PySpotExtension'

	# Get the header switch
	if sys.argv[1] == '-h':
		create_header(name)
	else:
		# Get the command line argument
		components = sys.argv[1:]
		create_source(name, components)


main()
