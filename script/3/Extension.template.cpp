#include "{{ extension }}/extension/{{ Extension }}.h"

{%- for component in components %}
#include "{{ extension }}/{{ component['namespace']|replace( '::', '/' ) }}/{{ component['name'] }}.h"
{%- endfor %}

static PyObject* g_{{ Extension }}Error;
static char g_a{{ Extension }}Error[{{ extension|length + 7 }}] = { "{{ extension }}.error" };

struct ModuleState
{
	PyObject* error;
};

#include "{{ extension }}/extension/{{ Extension }}.incl.cpp"

static PyMethodDef g_MethodDef[] = {
	{%- for method in methods %}
	{ "{{ method['name'] }}", {{ method['name'] }}, METH_VARARGS, "{{ method['description'] }}" },
	{%- endfor %}
	{ nullptr, nullptr, 0, nullptr } // Sentinel
};


static char g_a{{ Extension }}Description[{{ extension|length + 1 }}] = { "{{ Extension }}" };


static struct PyModuleDef g_ModuleDef
{
	PyModuleDef_HEAD_INIT,
	g_a{{ Extension }}Description,
	nullptr,
	sizeof( ModuleState ),
	g_MethodDef,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
};


PyMODINIT_FUNC PyInit_{{ extension }}()
{
	// Create the module
	PyObject* module{ PyModule_Create( &g_ModuleDef ) };
	if ( module == nullptr )
	{
		return nullptr;
	}

	// Module exception
	g_{{ Extension }}Error = PyErr_NewException( g_a{{ Extension }}Error, nullptr, nullptr );
	Py_INCREF( g_{{ Extension }}Error );
	PyModule_AddObject( module, "error", g_{{ Extension }}Error );

{% for component in components %}
	{%- set CompName = 'g_' ~ Extension ~ component['name'] ~ 'TypeObject' %}
	if ( PyType_Ready( &{{ CompName }} ) < 0 )
	{
		return nullptr;
	}
	{%- if 'values' in component %}
	{%- for key, val in component['values'].items() %}
	PyDict_SetItemString( {{ CompName }}.tp_dict, "{{ key }}", Wrapper<{{ '%s::%s' % ( component['namespace'], component['name'] ) }}>{ {{ '%s::%s::%s' % ( component['namespace'], component['name'], key ) }} }.GetIncref() );
	{%- endfor %}
	{%- endif %}
	Py_INCREF( &{{ CompName }} );
	PyModule_AddObject( module, "{{ component['name'] }}", reinterpret_cast<PyObject*>( &{{ CompName }} ) );
{% endfor %}

	return module;
}
