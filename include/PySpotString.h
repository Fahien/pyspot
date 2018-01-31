#ifndef PST_PYSPOTSTRING_H_
#define PST_PYSPOTSTRING_H_

#include "PySpotObject.h"

namespace pyspot
{

class PySpotString : public PySpotObject
{
public:
	PySpotString(PyObject* object);
	PySpotString(const char* str);
	~PySpotString();
};

}

#endif // PST_PYSPOTSTRING_H_
