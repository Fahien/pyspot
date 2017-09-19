#ifndef PST_PYSPOTOBJECT_H
#define PST_PYSPOTOBJECT_H

#include <Python.h>
#include <string>

namespace pyspot
{

class PySpotObject
{
public:
	PySpotObject();
	PySpotObject(PyObject * object_);
	~PySpotObject();

	PySpotObject(const PySpotObject & other);
	PySpotObject & operator=(const PySpotObject & other);

	inline PyObject * getObject() const { return object_; }
	inline std::wstring toString() const { return PyUnicode_AS_UNICODE(object_); }

protected:
	PyObject * object_;
};

}

#endif // PST_PYSPOTOBJECT_H
