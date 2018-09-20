#ifndef PST_{{ EXTENSION ~ COMPONENT }}_H_
#define PST_{{ EXTENSION ~ COMPONENT }}_H_

#include <cstring>
#include <pyspot/Interpreter.h>
#include <pyspot/String.h>
#include <pyspot/Tuple.h>
#include <pyspot/Wrapper.h>

{% for include in includes %}
#include "{{ extension }}/{{ include['namespace']|replace( '::', '/' ) }}/{{ include['name'] }}.h"
{%- endfor %}

{%- if header %}
#include <{{ header }}>
{%- else %}
#include <{{ '%s/%s.h' % (namespace|replace( '::', '/' ), Component) }}>
{%- endif %}

#include <structmember.h> // at the end

{%- set member_list = [] %}
{% set member_parsers = [] %}
{%- for member in members %}
	{%- set _ = member.update(static='g_a%s%s_%s' % (Extension, Component, member['name']|capitalize)) %}
	{%- set _ = member_list.append(member['static']) %}
	{%- set _ = member_parsers.append(parser_for_type(member['type'])) %}
static char {{ member['static'] }}[{{ member['name']|length + 1 }}] = { {{ '"%s"' % member['name'] }} };
{%- endfor %}
{% set _ = member_list.append('nullptr') %}
{%- for method in methods %}
	{%- set _ = method.update(static='g_a%s%sMethod_%s' % (Extension, Component, method['name'])) %}
static char {{ method['static'] }}[{{ method['name']|length + 1 }}] = { {{ '"%s"' % method['name'] }} };
{%- endfor %}

/// {{ Component }} destructor
static void {{ Extension ~ Component }}_Dealloc(_PyspotWrapper* self)
{
	{%- if destructible %}
	if (self->ownData)
	{
		delete reinterpret_cast<{{ '%s::%s' % (namespace, Component) }}*>(self->data);
	}
	{%- endif %}
	Py_TYPE(self)->tp_free(reinterpret_cast<PyObject*>(self));
}


/// {{ Component }} init
static int {{ Extension ~ Component }}_Init(_PyspotWrapper* self, PyObject* args, PyObject* kwds)
{
	{%- for member in members %}
		{%- if not is_builtin_type(member['type']) %}
	PyObject* {{ member['name'] }}{ nullptr };
		{%- endif %}
	{%- endfor %}

	static char* kwlist[]{ {{ member_list|join(', ') }} };
	static const char* fmt{ "|{{ member_parsers|join() }}" };

	{{ '%s::%s' % (namespace, Component) }}* data{ nullptr };

	if (self->data)
	{
		data = reinterpret_cast<{{ '%s::%s' % (namespace, Component) }}*>(self->data);
	}
	else
	{
{%- if constructible %}
		data = new {{ '%s::%s' % (namespace, Component) }};
		self->data = data;
		self->ownData = true;
{%- else %}
		return 0;
{%- endif %}
	}

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
{% endif %}
{%- endfor %}
	return 0;
}

/// Compare
static PyObject* {{ Extension ~ Component }}_Cmp( _PyspotWrapper* lhs, _PyspotWrapper* rhs, int op )
{
{%- if values|length > 0 %}
	if (op == Py_EQ)
	{
		auto& lData = *reinterpret_cast<{{ '%s::%s' % (namespace, Component) }}*>( lhs->data );
		auto& rData = *reinterpret_cast<{{ '%s::%s' % (namespace, Component) }}*>( rhs->data );
		
		if ( lData == rData )
		{
			Py_INCREF( Py_True );
			return Py_True;
		}
		else
		{
			Py_INCREF( Py_False );
			return Py_False;
		}
	}
{% endif %}
	Py_INCREF( Py_NotImplemented );
	return Py_NotImplemented;
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


{% for method in methods %}
static PyObject* {{ Extension ~ Component }}_Method_{{ method['name'] }}(_PyspotWrapper* self, PyObject* args, PyObject* kwds)
{
	{%- set args_list   = [] %}
	{%- set args_parsers = [] %}
	{%- set c_args_list  = [] %}
	{%- for arg in method['args'] %}
		{%- set _ = arg.update(static='a%s' % arg['name']|capitalize) %}
		{%- set _ = args_list.append(arg['static']) %}
		{%- set _ = args_parsers.append(parser_for_type(arg['type'])) %}
		
		{%- if is_builtin_type(arg['type']) %}
			{%- set _ = c_args_list.append(arg['name']) %}
		{%- else %}
			{%- set _ = c_args_list.append(to_c_type(arg['type']) % arg['name']) %}
		{%- endif %}
	static char {{ arg['static'] }}[{{ arg['name']|length + 1 }}] = { {{ '"%s"' % arg['name'] }} };
	{%- endfor %}
	{%- set _ = args_list.append('nullptr') %}

	{%- for arg in method['args'] %}
	{%- if is_builtin_type(arg['type']) %}
	{{ c_for_type(arg['type']) % arg['name'] }};
	{%- else %}
	PyObject* {{ arg['name'] }}{ nullptr };
	{%- endif %}
	{%- endfor %}

	static char* {{ 'a%s%s_Method_%s_kwlist' % (namespace, Component, method['name']) }}[]{ {{ args_list|join(', ') }} };
	static const char* {{ 'a%s%s_Method_%s_fmt' % (namespace, Component, method['name']) }}{ "{{ args_parsers|join() }}|" };

	if (!PyArg_ParseTupleAndKeywords(args, kwds, {{ 'a%s%s_Method_%s_fmt' % (namespace, Component, method['name']) }}, {{ 'a%s%s_Method_%s_kwlist' % (namespace, Component, method['name']) }}
		{%- for arg in method['args'] %}, &{{ arg['name'] }}{%- endfor %}))
	{
		return Py_None;
	}
{% for arg in method['args'] %}
	{%- if not is_builtin_type(arg['type']) %}
	if (!{{ arg['name'] }})
	{
		return Py_None;
	}
	{%- endif %}
{%- endfor %}

	auto data = reinterpret_cast<{{ '%s::%s' % ( namespace, Component ) }}*>( self->data );
	
{%- if method['type'] == 'void' %}
	data->{{ method['name'] }}( {{ c_args_list|join( ',' ) }} );
	return Py_None;
{%- else %}
	return {{ to_python_type( method['type'] ) % ( 'data->' ~ method['name'] ~ '(' ~ c_args_list|join( ',' ) ~ ')' ) }};
{%- endif %}
}
{% endfor %}


static PyMethodDef {{ Extension ~ Component }}_methods[]
{
	{%- for method in methods %}
	{
		{{ method['static'] }},
		reinterpret_cast<PyCFunction>({{ Extension ~ Component }}_Method_{{ method['name'] }}),
		{{ method_flags_for_args(method['args']) }},
		{{ '"%s::%s::%s"' % (namespace, Component, method['name']) }}
	},
	{%- endfor %}
	{ nullptr } // Sentinel
};


static PyTypeObject g_{{ Extension ~ Component }}TypeObject = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	"{{ extension }}.{{ Component }}",
	sizeof( _PyspotWrapper ),
	0,

	reinterpret_cast<destructor>( {{ Extension ~ Component }}_Dealloc ),
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

	reinterpret_cast<richcmpfunc>( {{ Extension ~ Component }}_Cmp ),

	0,

	0,
	0,

	{{ Extension ~ Component }}_methods,
	{{ Extension ~ Component }}_members,
	{{ Extension ~ Component }}_accessors,
	0,
	0,
	0,
	0,
	0,
	reinterpret_cast<initproc>( {{ Extension ~ Component }}_Init ),
	0,
	PyspotWrapper_New,
};



template<>
pyspot::Wrapper<{{ "%s::%s" % ( namespace, Component ) }}>::Wrapper( {{ '%s::%s' % (namespace, Component) }}& t )
{%- if constructible %}
:	pyspot::Object { ( PyType_Ready( &g_{{ Extension ~ Component }}TypeObject ), PyspotWrapper_New( &g_{{ Extension ~ Component }}TypeObject, nullptr, nullptr ) ) }
,	payload{ &t }
{
	auto {{ component }} = reinterpret_cast<_PyspotWrapper*>( mObject );
	{{ component }}->data = payload;
}
{% else %}	= delete;{% endif %}


template<>
pyspot::Wrapper<{{ "%s::%s" % ( namespace, Component ) }}>::Wrapper( {{ '%s::%s' % ( namespace, Component ) }}* t )
:	pyspot::Object { ( PyType_Ready( &g_{{ Extension ~ Component }}TypeObject ), PyspotWrapper_New( &g_{{ Extension ~ Component }}TypeObject, nullptr, nullptr ) ) }
,	payload{ t }
{
	auto {{ component }} = reinterpret_cast<_PyspotWrapper*>( mObject );
	{{ component }}->data = t;
}


template<>
pyspot::Wrapper<{{ "%s::%s" % ( namespace, Component ) }}>::Wrapper( {{ '%s::%s' % ( namespace, Component ) }}&& t )
{%- if constructible %}
:	pyspot::Object { ( PyType_Ready( &g_{{ Extension ~ Component }}TypeObject ), PyspotWrapper_New( &g_{{ Extension ~ Component }}TypeObject, nullptr, nullptr ) ) }
,	payload { new {{ '%s::%s' % ( namespace, Component ) }} { std::move( t ) } }
{
	auto {{ component }} = reinterpret_cast<_PyspotWrapper*>( mObject );
	{{ component }}->data = payload;
	{{ component }}->ownData = true;
}
{% else %}	= delete;{% endif %}


#endif // PST{{ EXTENSION ~ COMPONENT }}_H_
