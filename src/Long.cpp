#include <Python.h>

#include "pyspot/Long.h"


namespace pyspot
{


Long::Long(PyObject* object)
:	Object{ object }
{}


Long::Long(const long l)
:	Object{ PyLong_FromLong(l) }
{}


Long::~Long()
{}


} // namespace pyspot
