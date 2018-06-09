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
