#include "pyspot/Dictionary.h"

namespace pyspot
{


Dictionary::Dictionary()
:	Object{ PyDict_New() }
{}


Dictionary::Dictionary(PyObject* pObject)
:	Object{ pObject }
{
	assert( PyDict_Check(pObject) && "Object must be a dictionary");
}


Dictionary::Dictionary(const Object& other)
:	Object{ (PyDict_Check(other.GetObject()), other.GetIncref()) }
{}


Dictionary::~Dictionary()
{
	PyDict_Clear(mObject);
}


void Dictionary::SetItem(const char* key, Object& val)
{
	PyDict_SetItemString(mObject, key, val.GetObject());
}


void Dictionary::SetItem(const std::string& key, Object& val)
{
	SetItem(key.c_str(), val);
}


void Dictionary::SetItem(const Object& key, Object& val)
{
	PyDict_SetItem(mObject, key.GetObject(), val.GetObject());
}


} // namespace pyspot
