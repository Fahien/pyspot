#ifndef PYSPOT_BOOL_H_
#define PYSPOT_BOOL_H_


#include "pyspot/Object.h"


namespace pyspot
{


class Bool : Object
{
  public:
	Bool( Object&& object );
	Bool( const bool b = false );

	operator bool() { return value; }

  private:
	bool value;
};


} // namespace pyspot


#endif // PYSPOT_BOOL_H_
