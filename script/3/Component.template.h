#ifndef PST_{{ EXTENSION ~ COMPONENT }}_H_
#define PST_{{ EXTENSION ~ COMPONENT }}_H_

#include <cstring>
#include <pyspot/Interpreter.h>
#include <pyspot/String.h>
#include <pyspot/Tuple.h>
#include <pyspot/Wrapper.h>
{% for include in includes %}
#include "{{ extension }}/{{ include['namespace'] }}/{{ include['name'] }}.h"
{% endfor %}
#include <{{ '%s/%s.h' % (namespace, Component) }}>
#include <structmember.h> // at the end

{%- set member_list = [] %}
{% set member_parsers = [] %}
{%- for member in members %}
	{%- set _ = member.update(static='g_a%s%s%s' % (Extension, Component, member['name']|capitalize)) %}
	{%- set _ = member_list.append(member['static']) %}
	{%- set _ = member_parsers.append(parser_for_type(member['type'])) %}
static char {{ member['static'] }}[{{ member['name']|length + 1 }}] = { {{ '"%s"' % member['name'] }} };
{%- endfor %}
{%- set _ = member_list.append('nullptr') %}


/// {{ Component }} destructor
static void {{ Extension ~ Component }}_Dealloc(_PyspotWrapper* self)
{
	if (self->ownData)
	{
		delete reinterpret_cast<{{ '%s::%s' % (namespace, Component) }}*>(self->data);
	}
	{%- for member in members %}
		{%- if not is_builtin_type(member['type']) %}
	//Py_XDECREF(self->{{ member['name'] }});
		{%- endif %}
	{%- endfor %}
	Py_TYPE(self)->tp_free(reinterpret_cast<PyObject*>(self));
}


/// {{ Component }} init
static int {{ Extension ~ Component }}_Init(_PyspotWrapper* self, PyObject* args, PyObject* kwds)
{
	{%- for member in members %}
	{% if not is_builtin_type(member['type']) %}PyObject* temp{ nullptr };{% break %}{%- endif %}
	{%- endfor %}

	{%- for member in members %}
		{%- if not is_builtin_type(member['type']) %}
	PyObject* {{ member['name'] }}{ nullptr };
		{%- endif %}
	{%- endfor %}

	static char* kwlist[]{ {{ member_list|join(', ') }} };
	static const char* fmt{ "|{{ member_parsers|join() }}" };

	auto data = reinterpret_cast<{{ '%s::%s' % (namespace, Component) }}*>(self->data);

	if (!PyArg_ParseTupleAndKeywords(args, kwds, fmt, kwlist
		{%- for member in members %}, &{{ 'data->' if is_builtin_type(member['type']) }}{{ member['name'] }}{%- endfor %}))
	{
		return -1;
	}

{% for member in members %}
{%- if not is_builtin_type(member['type']) %}
	if ({{ member['name'] }})
	{
		data->{{ member['name'] }} = {{ to_c_type(member['type']) % member['name'] }};
	}
{%- endif %}
{%- endfor %}

	return 0;
}


static PyMemberDef {{ Extension ~ Component }}_members[]
{
	{ nullptr } // Sentinel
};

{% for member in members %}
static PyObject* {{ Extension ~ Component }}_Get{{ member['name']|capitalize }}(_PyspotWrapper* self, void* closure)
{
	auto data = reinterpret_cast<{{ '%s::%s' % (namespace, Component) }}*>(self->data);
	return {{ to_python_type(member['type']) % ('data->' ~ member['name']) }};
}

static int {{ Extension ~ Component }}_Set{{ member['name']|capitalize }}(_PyspotWrapper* self, PyObject* value, void* closure)
{
	if (value == nullptr)
	{
		PyErr_SetString(PyExc_TypeError, "Cannot delete {{ member['name'] }} attribute");
		return -1;
	}

	{%- if member['type'] == 'string' %}
	if (!PyUnicode_Check(value))
	{
		PyErr_SetString(PyExc_TypeError, "The {{ member['name'] }} attribute value must be a string");
		return -1;
	}

	{%- endif %}

	auto data = reinterpret_cast<{{ '%s::%s' % (namespace, Component) }}*>(self->data);
	data->{{ member['name'] }} = {{ to_c_type(member['type']) % 'value' }};

	return 0;
}
{% endfor %}

static PyGetSetDef {{ Extension ~ Component }}_accessors[]
{
	{%- for member in members %}
	{ {{ member['static'] }}, (getter){{ Extension ~ Component }}_Get{{ member['name']|capitalize }}, (setter){{ Extension + Component }}_Set{{ member['name']|capitalize }}, {{ member['static'] }}, nullptr },
	{%- endfor %}
	{ nullptr } // Sentinel
};


static PyTypeObject g_{{ Extension ~ Component }}TypeObject = {
	PyVarObject_HEAD_INIT(NULL, 0)

	"{{ extension }}.{{ Component }}",
	sizeof(_PyspotWrapper),
	0,

	reinterpret_cast<destructor>({{ Extension ~ Component }}_Dealloc),
	0,
	0,
	0,
	0,
	0,

	0,
	0,
	0,

	0,
	0,
	0,
	0,
	0,

	0,

	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,

	"{{ Extension ~ Component }}",

	0,

	0,

	0,

	0,

	0,
	0,

	0,
	{{ Extension ~ Component }}_members,
	{{ Extension ~ Component }}_accessors,
	0,
	0,
	0,
	0,
	0,
	reinterpret_cast<initproc>({{ Extension ~ Component }}_Init),
	0,
	PyspotWrapper_New,
};


namespace pyspot
{

template<>
Wrapper<{{ "%s::%s" % (namespace, Component) }}>::Wrapper({{ '%s::%s' % (namespace, Component) }}& t)
:	Object { (PyType_Ready(&g_{{ Extension ~ Component }}TypeObject), PyspotWrapper_New(&g_{{ Extension ~ Component }}TypeObject, nullptr, nullptr)) }
,	payload{ t }
{
	auto {{ component }} = reinterpret_cast<_PyspotWrapper*>(mObject);
	{{ component }}->data = &t;
}

}


#endif // PST{{ EXTENSION ~ COMPONENT }}_H_
