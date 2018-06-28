#include "pyspot/Dictionary.h"

using namespace pyspot;


Dictionary::Dictionary()
:	Object{ PyDict_New() }
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
