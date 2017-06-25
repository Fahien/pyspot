#include <stdio.h>
#include <Python.h>
#include "PySpotString.h"

using namespace pyspot;


PySpotString::PySpotString(const char * str)
{
	object_ = PyUnicode_FromString(str);
	printf("Created PySpotString %p\n", object_);
}


PySpotString::~PySpotString()
{
	printf("Destroying PySpotString %p\n", object_);
}
