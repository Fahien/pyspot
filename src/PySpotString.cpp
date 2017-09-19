#include <stdio.h>
#include <Python.h>
#include <PySpotString.h>

using namespace pyspot;


PySpotString::PySpotString(const char* str)
{
	mObject = PyUnicode_FromString(str);
	printf("Created PySpotString %p\n", mObject);
}


PySpotString::~PySpotString()
{
	printf("Destroying PySpotString %p\n", mObject);
}
