#include "{{ extension }}/extension/{{ Extension }}.h"

{%- for component in components %}
{{ '#include "%s/component/%s.h"' % (extension, component) }}
{%- endfor %}

static PyObject* pstError;

struct ModuleState
{
	PyObject* error;
};

#include "{{ extension }}/extension/{{ Extension }}.incl.cpp"

static PyMethodDef pstMethods[] = {
	{%- for method in methods %}
	{ "{{ method['name'] }}", {{ method['name'] }}, METH_VARARGS, "{{ method['description'] }}" },
	{%- endfor %}
	{ nullptr, nullptr, 0, nullptr } // Sentinel
};

static struct PyModuleDef moduleDef
{
	PyModuleDef_HEAD_INIT,
	"{{ extension }}",
	nullptr,
	sizeof(ModuleState),
	pstMethods,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
};


PyMODINIT_FUNC PyInit_{{ Extension }}()
{
	// Create the module
	PyObject* module{ PyModule_Create(&moduleDef) };
	if (module == nullptr)
	{
		return nullptr;
	}

	// Module exception
	pstError = PyErr_NewException("{{ extension }}.error", nullptr, nullptr);
	Py_INCREF(pstError);
	PyModule_AddObject(module, "error", pstError);

	{%- for component in components %}
	if (PyType_Ready(&{{ extension }}{{ component }}) < 0)
	{
		return nullptr;
	}
	Py_INCREF(&{{ extension }}{{ component }});
	PyModule_AddObject(module, "{{ component }}", reinterpret_cast<PyObject*>(&{{ extension }}{{ component }}));
	{%- endfor %}

	return module;
}
