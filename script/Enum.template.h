#ifndef PST_{{ EXTENSION + ENUM }}_H_
#define PST_{{ EXTENSION + ENUM }}_H_

#include <Python.h>
#include <pyspot/Long.h>
#include <structmember.h> // at the end


/// {{ Enum }}
struct {{ Extension + Enum }}
{
	PyObject_HEAD
};


/// {{ Enum }} constructor
static PyObject* {{ Extension + Enum }}_New(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	return type->tp_alloc(type, 0);
}


/// {{ Enum }} destructor
static void {{ Extension + Enum }}_Dealloc({{ Extension + Enum }}* self)
{
	Py_TYPE(self)->tp_free(reinterpret_cast<PyObject*>(self));
}

/// {{ Enum }} object
static PyTypeObject {{ extension ~ Enum }} = {
	PyVarObject_HEAD_INIT(NULL, 0) "{{ extension }}.{{ namespace }}.{{ Enum }}",
	sizeof({{ Extension + Enum }}),
	0,
	(destructor){{ Extension ~ Enum }}_Dealloc,
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
	"{{ Extension + Enum }} object",
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
	0,
	0,
	{{ Extension + Enum }}_New,
};



// Wrapper
namespace {{ extension }}
{

namespace {{ namespace }}
{


enum class {{ Enum }} : long
{
	{%- for key, val in values.items() %}
	{{ key|upper }} = {{ val }},
	{%- endfor %}
};


static pyspot::Long to_python(const {{ Enum }}& v)
{
	return pyspot::Long{ static_cast<long>(v) };
}


}

}


#endif // PST{{ EXTENSION + ENUM }}_H_
