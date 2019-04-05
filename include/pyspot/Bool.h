#ifndef PYSPOT_BOOL_H_
#define PYSPOT_BOOL_H_


#include "pyspot/Object.h"


namespace pyspot
{
class Bool : public Object
{
  public:
	Bool( Object&& object );
	Bool( const bool b = false );

	operator bool() const { return value; }

  private:
	bool value;
};


}  // namespace pyspot

#endif  // PYSPOT_BOOL_H_
