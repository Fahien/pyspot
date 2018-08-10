#ifndef PST_WRAPPER_H_
#define PST_WRAPPER_H_

#include <cassert>

#include <pyspot/Object.h>
#include <structmember.h> // at the end


/// Wrapper
struct _PyspotWrapper
{
	PyObject_HEAD
	void* data;
	bool ownData;
};



/// Constructor
static PyObject* PyspotWrapper_New(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	auto self = reinterpret_cast<_PyspotWrapper*>(type->tp_alloc(type, 0));

	if (self != nullptr)
	{
		self->data = nullptr;
		self->ownData = false;
	}

	return reinterpret_cast<PyObject*>(self);
}


/// Destructor
static void PyspotWrapper_Dealloc(_PyspotWrapper* self)
{
	// If it owns the data, it needs a specific destructor
	assert(!self->ownData);
	Py_TYPE(self)->tp_free(reinterpret_cast<PyObject*>(self));
}


/// Init
static int PyspotWrapper_Init(_PyspotWrapper* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[]{ nullptr };
	static const char* fmt{ "|" };

	if (!PyArg_ParseTupleAndKeywords(args, kwds, fmt, kwlist))
	{
		return -1;
	}

	return 0;
}


/// Members
static PyMemberDef PyspotWrapper_members[]
{
	{ nullptr } // Sentinel
};


/// PyTypeObject
static PyTypeObject PyspotWrapperTypeObject = {
	PyVarObject_HEAD_INIT(NULL, 0)

	"pyspot.Wrapper",       // name
	sizeof(_PyspotWrapper), // basicsize
	0,                      // itemsize

	reinterpret_cast<destructor>(PyspotWrapper_Dealloc), // destructor
	0, 	                                                 // print
	0, 	                                                 // getattr
	0, 	                                                 // setattr
	0, 	                                                 // compare
	0, 	                                                 // repr

	0, // as_number
	0, // as_sequence
	0, // as_mapping

	0, // hash
	0, // call
	0, // str
	0, // getattro
	0, // setattro

	0, // as_buffer

	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, // flags

	"Pyspot Wrapper", // doc

	0, // traverse

	0, // clear

	0, // richcompare

	0, // weaklistoffset

	0, // iter
	0, // iternext

	0,                                              // methods
	PyspotWrapper_members,                          // members
	0,                                              // getset
	0,                                              // base
	0,                                              // dict
	0,                                              // descr_get
	0,                                              // descr_set
	0,                                              // dictoffset
	reinterpret_cast<initproc>(PyspotWrapper_Init), // init
	0,                                              // alloc
	PyspotWrapper_New,                              // new
};


namespace pyspot
{

template<typename T>
class Wrapper : public Object
{
  public:
	Wrapper(const Object& object)
	:	Object { object }
	,	payload{ reinterpret_cast<T*>(reinterpret_cast<_PyspotWrapper*>(mObject)->data) }
	{}

	Wrapper(const T&);
	Wrapper(T*);
	Wrapper(T&&);

	T& GetPayload() const { return *payload; }
	T& operator*()  const { return *payload; }
	T* operator->() const { return  payload; }

  private:
	T* payload;
};


}


#endif // PST_WRAPPER_H_