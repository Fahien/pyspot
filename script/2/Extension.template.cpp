#include "{{ extension }}/extension/{{ Extension }}.h"

{%- for component in components %}
#include "{{ extension }}/{{ component['namespace'] }}/{{ component['name'] }}.h"
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


static char a{{ Extension }}Error[{{ extension|length + 7 }}] = { "{{ extension }}.error" };

PyMODINIT_FUNC PyInit_{{ Extension }}()
{
	// Create the module
	PyObject* module{ Py_InitModule("{{ extension }}", pstMethods) };
	if (module == nullptr)
	{
		return;
	}

	// Module exception
	pstError = PyErr_NewException(a{{ Extension }}Error, nullptr, nullptr);
	Py_INCREF(pstError);
	PyModule_AddObject(module, "error", pstError);

{% for component in components %}
	if (PyType_Ready(&{{ extension ~ component['name'] }}) < 0)
	{
		return;
	}
	{%- if 'values' in component %}
	{%- for key, val in component['values'].items() %}
	PyDict_SetItemString({{ extension ~ component['name'] }}.tp_dict, "{{ key }}", PyLong_FromLong({{ val }}));
	{%- endfor %}
	{%- endif %}
	Py_INCREF(&{{ extension ~ component['name'] }});
	PyModule_AddObject(module, "{{ component['name'] }}", reinterpret_cast<PyObject*>(&{{ extension ~ component['name'] }}));
{% endfor %}
}
