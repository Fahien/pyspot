#ifndef PST_DICTIONARY_H_
#define PST_DICTIONARY_H_

#include "Object.h"

namespace pyspot
{


class Dictionary : public Object
{
  public:
	Dictionary();
	~Dictionary();

	void SetItem(const char* key, Object& val);

  private:

};


}


#endif // PST_DICTIONARY_H_
