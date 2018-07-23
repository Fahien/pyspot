#ifndef PST_ERROR_H_
#define PST_ERROR_H_

#include <string>

#include "pyspot/common.h"


namespace pyspot
{


class Error
{
  public:
	static void Check();
	static tstring Get();
};


}


#endif // PST_ERROR_H_