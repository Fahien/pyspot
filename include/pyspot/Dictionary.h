#ifndef PST_DICTIONARY_H_
#define PST_DICTIONARY_H_

#include <string>

#include "pyspot/Object.h"

namespace pyspot
{

class String;


class Dictionary : public Object
{
  public:
	Dictionary();
	Dictionary( PyObject* pObject );
	Dictionary( const Object& other );
	~Dictionary();

	size_t GetSize() const { return static_cast<size_t>( PyDict_Size( object ) ); }

	void SetItem( const char* key, Object& val );
	void SetItem( const std::string& key, Object& val );
	void SetItem( const Object& key, Object& value );

  private:
};


}


#endif // PST_DICTIONARY_H_
