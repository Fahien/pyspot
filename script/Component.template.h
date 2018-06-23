#ifndef PST_{{ EXTENSION ~ COMPONENT }}_H_
#define PST_{{ EXTENSION ~ COMPONENT }}_H_

#include <cstring>
#include <pyspot/Interpreter.h>
#include <pyspot/String.h>
#include <pyspot/Tuple.h>
{% for include in includes %}
#include "{{ extension }}/{{ include['namespace'] }}/{{ include['name'] }}.h"
{% endfor %}
#include <structmember.h> // at the end

{%- set member_list = [] %}
{%- set member_parsers = [] %}
{%- for member in members %}
	{%- set _ = member.update(static='a%s%s%s' % (Extension, Component, member['name']|capitalize)) %}
	{%- set _ = member_list.append(member['static']) %}
	{%- set _ = member_parsers.append(parser_for_type(member['type'])) %}
	{%- set _ = member_list.append('nullptr') %}

static char {{ member['static'] }}[{{ member['name']|length + 1 }}] = { {{ '"%s"' % member['name'] }} };
{%- endfor %}

/// {{ Component }}
struct {{ Extension ~ Component }}
{
	PyObject_HEAD
	{%- for member in members %}
		{%- if is_builtin_type(member['type']) %}
			{%- set type = c_for_type(member['type']) %}
		{%- else %}
			{%- set type = 'PyObject* %s' %}
		{%- endif %}
	{{ type % member['name'] }};
	{%- endfor %}
};


/// {{ Component }} constructor
static PyObject* {{ Extension ~ Component }}_New(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	{{ Extension ~ Component }}* self{ reinterpret_cast<{{ Extension ~ Component }}*>(type->tp_alloc(type, 0)) };

	if (self != nullptr)
	{
		{%- for member in members %}
			{%- set default = member['default'] if 'default' in member else None %}
		self->{{ member['name'] }} = {{ initializer_for_type(extension, member['type'], default) }};
			{#- Check non builtin types #}
			{%- if not is_builtin_type(member['type']) %}
		if (self->{{ member['name'] }} == nullptr)
		{
			Py_DECREF(self);
			return nullptr;
		}
			{%- endif %}
		{%- endfor %}
	}

	return reinterpret_cast<PyObject*>(self);
}


/// {{ Component }} destructor
static void {{ Extension ~ Component }}_Dealloc({{ Extension ~ Component }}* self)
{
	{%- for member in members %}
		{%- if not is_builtin_type(member['type']) %}
	Py_XDECREF(self->{{ member['name'] }});
		{%- endif %}
	{%- endfor %}
	Py_TYPE(self)->tp_free(reinterpret_cast<PyObject*>(self));
}


static int {{ Extension ~ Component }}_Init({{ Extension ~ Component }}* self, PyObject* args, PyObject* kwds)
{
	PyObject* temp{ nullptr };
	{%- for member in members %}
		{%- if not is_builtin_type(member['type']) %}
	PyObject* {{ member['name'] }}{ nullptr };
		{%- endif %}
	{%- endfor %}

	static char* kwlist[]{ {{ member_list|join(', ') }} };
	static const char* fmt{ "|{{ member_parsers|join() }}" };

	if (!PyArg_ParseTupleAndKeywords(args, kwds, fmt, kwlist
		{%- for member in members %}, &{{ 'self->' if is_builtin_type(member['type']) }}{{ member['name'] }}{%- endfor %}))
	{
		return -1;
	}

	{%- for member in members %}
	{%- if not is_builtin_type(member['type']) %}

	if ({{ member['name'] }})
	{
		temp = self->{{ member['name'] }};
		Py_INCREF({{ member['name'] }});
		self->{{ member['name'] }} = {{ member['name'] }};
		Py_XDECREF(temp);
	}
	{%- endif %}
	{%- endfor %}

	return 0;
}


static PyMemberDef {{ Extension ~ Component }}_members[]
{
	{%- for member in members %}
	{%- if is_builtin_type(member['type']) %}
	{ {{ member['static'] }}, {{ pytype_for_type(member['type']) }}, offsetof({{ Extension ~ Component }}, {{ member['name'] }}), 0, {{ member['static'] }} },
	{%- endif %}
	{%- endfor %}
	{ nullptr } // Sentinel
};


{%- for member in members %}
{%- if not is_builtin_type(member['type']) %}

static PyObject* {{ Extension ~ Component }}_Get{{ member['name']|capitalize }}({{ Extension ~ Component }}* self, void* closure)
{
	Py_INCREF(self->{{ member['name'] }});
	return self->{{ member['name'] }};
}

static int {{ Extension ~ Component }}_Set{{ member['name']|capitalize }}({{ Extension ~ Component }}* self, PyObject* value, void* closure)
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
	Py_DECREF(self->{{ member['name'] }});
	Py_INCREF(value);
	self->{{ member['name'] }} = value;

	return 0;
}
{%- endif %}
{%- endfor %}


static PyGetSetDef {{ Extension ~ Component }}_accessors[]
{
	{%- for member in members %}
	{%- if not is_builtin_type(member['type']) %}
	{ {{ member['static'] }}, (getter){{ Extension ~ Component }}_Get{{ member['name']|capitalize }}, (setter){{ Extension + Component }}_Set{{ member['name']|capitalize }}, {{ member['static'] }}, nullptr },
	{%- endif %}
	{%- endfor %}
	{ nullptr } // Sentinel
};


static PyTypeObject {{ extension ~ Component }} = {
	PyVarObject_HEAD_INIT(NULL, 0) "{{ extension }}.{{ Component }}",
	sizeof({{ Extension ~ Component }}),
	0,
	(destructor){{ Extension ~ Component }}_Dealloc,
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
	"{{ Extension ~ Component }} object",
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
	(initproc){{ Extension ~ Component }}_Init,
	0,
	{{ Extension ~ Component }}_New,
};


namespace {{ extension }}
{

namespace {{ namespace }}
{

class {{ Component }} : public pyspot::Object
{
  public:
	{%- if values %}
	enum : long {
		{%- for key, val in values.items() %}
		{{ key|upper }} = {{ val }},
		{%- endfor %}
	};

	{{ Component }}(const long value)
	:	pyspot::Object{ PyLong_FromLong(value) }
	{}
	{%- endif %}

	{{ Component }}(PyObject* object)
	:	pyspot::Object{ object }
	{}

	{{ Component }}()
	:	pyspot::Object
		{
			(PyType_Ready(&{{ extension ~ Component }}), {{ Extension ~ Component }}_New(&{{ extension ~ Component }}, nullptr, nullptr))
		}
	{}

	{%- if members|length > 0 %}
		{%- set arguments = [] %}
		{%- for member in members %}
			{%- if is_builtin_type(member['type']) %}
				{%- set type = c_for_type(member['type']) %}
			{%- else %}
				{%- set type = 'pyspot::Object& %s' %}
			{%- endif %}
			{%- set _ = arguments.append(type % member['name']) %}
		{%- endfor %}

	{{ Component }}({{ arguments|join(', ') }})
	:	pyspot::Object
		{
			(PyType_Ready(&{{ extension ~ Component }}), {{ Extension ~ Component }}_New(&{{ extension ~ Component }}, nullptr, nullptr))
		}
	{
		pyspot::Tuple arguments{ {{ members|length }} };
		{%- for i in range(members|length) %}
		arguments.SetItem({{ i }}, {{ members[i]['name'] }});
		{%- endfor %}
		{{ Extension ~ Component }}_Init(GetComponent(), arguments.GetObject(), nullptr);
	}
	{%- endif %}

	~{{ Component }}(){}

	{{ Extension ~ Component }}* GetComponent()
	{
		return reinterpret_cast<{{ Extension ~ Component }}*>(GetObject());
	}

	{%- for member in members %}
	{%- set pyspot_type = pyspot_for_type(extension, member['type']) %}
	{{ pyspot_type }} Get{{ member['name']|capitalize }}()
	{
		{%- if is_builtin_type(member['type']) %}
		return GetComponent()->{{ member['name'] }};
		{%- else %}
		return {{ pyspot_type }}{ {{ Extension ~ Component }}_Get{{ member['name']|capitalize }}(GetComponent(), nullptr) };
		{%- endif %}
	}
	{%- endfor %}
};

}

}


#endif // PST{{ EXTENSION ~ COMPONENT }}_H_
