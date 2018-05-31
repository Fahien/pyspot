"""This script generates the PySpotExtension header"""

import sys
import json

PYINIT_FUNC_NAME = 'PyInit_PySpot'


def create_header(name):
	"""Creates the Extension header"""

	print('#ifndef PST_{0}_H\n#define PST_{0}_H\n'.format(name.upper()))

	print('#include "pyspot/Interpreter.h"\n')
	print('PyMODINIT_FUNC %s();\n' % PYINIT_FUNC_NAME)
	print('#endif // PST_%s_H' % name.upper())


def create_source(name, components):
	"""Creates the Extension source"""

	print('#include "pyspot/extension/%s.h"' % name)
	# Name of the components
	for component in components:
		print('#include "pyspot/component/%s.h"' % component)
	print('\n#define GETSTATE(m) (reinterpret_cast<ModuleState*>(PyModule_GetState(m)))\n')
	print('static PyObject* pstError;\n')
	print('struct ModuleState\n{\n\tPyObject* error;\n};\n')
	print('static struct PyModuleDef moduleDef\n{')
	print('\tPyModuleDef_HEAD_INIT,')
	print('\t"pyspot",')
	print('\tnullptr,')
	print('\tsizeof(ModuleState),')
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
		component_var = component.lower()
		print('\tif (PyType_Ready(&pyspot%s) < 0)\n\t{\n\t\treturn nullptr;\n\t}' % component_var)
		print('\tPy_INCREF(&pyspot%s);' % component_var)
		print('\tPyModule_AddObject(module, "{0}", reinterpret_cast<PyObject*>(&pyspot{1}));\n'.format(component, component_var))

	print('\treturn module;\n};')


def main():
	"""Entry point"""

	if len(sys.argv) < 2:
		exit('Usage:\n\t{0} <list of components>\n\t{0} -h' % sys.argv[0])

	name = 'Extension'

	# Get the header switch
	if sys.argv[1] == '-h':
		create_header(name)
	else:
		# Get the command line argument
		components = sys.argv[1:]
		create_source(name, components)


main()
