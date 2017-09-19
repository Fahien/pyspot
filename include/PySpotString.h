#ifndef PST_PYSPOTSTRING_H
#define PST_PYSPOTSTRING_H

#include <PySpotObject.h>

namespace pyspot
{

class PySpotString : public PySpotObject
{
public:
	PySpotString(const char* str);
	~PySpotString();
};

}

#endif // PST_PYSPOTSTRING_H
