#ifndef PST_PYSPOTOBJECT_H
#define PST_PYSPOTOBJECT_H

#include <Python.h>

namespace pyspot
{

class PySpotObject
{
public:
	PySpotObject();
	~PySpotObject();

	PySpotObject(const PySpotObject & other);
	PySpotObject & operator=(const PySpotObject & other);

	inline PyObject * getObject() const { return object_; }

protected:
	PyObject * object_;
};

}

#endif // PST_PYSPOTOBJECT_H
