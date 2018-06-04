#include "pyspot/extension/${Extension}.h"

${include_components}

static PyObject* pstError;

struct ModuleState
{
	PyObject* error;
};

#include "pyspot/extension/${Extension}.incl.cpp"

static PyMethodDef pstMethods[] = {
${list_methods}
};

static struct PyModuleDef moduleDef
{
	PyModuleDef_HEAD_INIT,
	"${extension}",
	nullptr,
	sizeof(ModuleState),
	pstMethods,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
};


PyMODINIT_FUNC PyInit_${Extension}()
{
	// Create the module
	PyObject* module{ PyModule_Create(&moduleDef) };
	if (module == nullptr)
	{
		return nullptr;
	}

	// Module exception
	pstError = PyErr_NewException("${extension}.error", nullptr, nullptr);
	Py_INCREF(pstError);
	PyModule_AddObject(module, "error", pstError);

${add_components}

	return module;
}