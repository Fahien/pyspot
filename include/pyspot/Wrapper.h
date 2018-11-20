#ifndef PST_WRAPPER_H_
#define PST_WRAPPER_H_

#include <cassert>

#include <pyspot/Object.h>
#include <structmember.h> // at the end


/// Wrapper
struct _PyspotWrapper
{
	PyObject_HEAD
	void* pData;
	bool bOwnData;
};



/// Constructor
static PyObject* PyspotWrapper_New( PyTypeObject* type, PyObject* args, PyObject* kwds )
{
	auto pSelf = reinterpret_cast<_PyspotWrapper*>( type->tp_alloc( type, 0 ) );

	if ( pSelf != nullptr )
	{
		pSelf->pData = nullptr;
		pSelf->bOwnData = false;
	}

	return reinterpret_cast<PyObject*>( pSelf );
}


/// Destructor
static void PyspotWrapper_Dealloc( _PyspotWrapper* pSelf )
{
	// If it owns the pData, it needs a specific destructor
	assert( !pSelf->bOwnData );
	Py_TYPE( pSelf )->tp_free( reinterpret_cast<PyObject*>( pSelf ) );
}


/// Init
static int PyspotWrapper_Init( _PyspotWrapper*, PyObject*, PyObject* )
{
	return 0;
}


/// Members
static PyMemberDef g_PyspotWrapper_members[]
{
	{ nullptr } // Sentinel
};


/// PyTypeObject
static PyTypeObject g_PyspotWrapperTypeObject {
	PyVarObject_HEAD_INIT( nullptr, 0 )

	"pyspot.Wrapper",         // name
	sizeof( _PyspotWrapper ), // basicsize
	0,                        // itemsize

	reinterpret_cast<destructor>( PyspotWrapper_Dealloc ), // destructor
	0,                                                     // print
	0,                                                     // getattr
	0,                                                     // setattr
	0,                                                     // compare
	0,                                                     // repr

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
	g_PyspotWrapper_members,                        // members
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
	Wrapper( const Object& object )
	:	Object { object }
	,	pPayload{ reinterpret_cast<T*>( reinterpret_cast<_PyspotWrapper*>( mObject )->pData ) }
	{}

	Wrapper( T& );
	Wrapper( T* );
	Wrapper( T&& );

	T& GetPayload() const { return *pPayload; }
	T& operator*()  const { return *pPayload; }
	T* operator->() const { return  pPayload; }

  private:
	T* pPayload;
};


} // namespace pyspot


#endif // PST_WRAPPER_H_
