#ifndef PST_PYSPOT_H
#define PST_PYSPOT_H

#include <string>
#include <PySpotModule.h>


namespace pyspot
{

class PySpot
{
public:
	PySpot();
	~PySpot();

	PySpotModule importModule(const char* name);

private:
	void addToPath(const wchar_t* folder);

	std::wstring mPath;
};

}

#endif // PST_PYSPOT_H
