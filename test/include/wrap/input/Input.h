#ifndef WRAP_INPUT_H_
#define WRAP_INPUT_H_

#include "wrap/input/Key.h"
#include "wrap/input/Action.h"

namespace wrap
{

namespace input
{


class Input
{
  public:
	inline Input( Key k = Key::UP, Action a = Action::RELEASE );

	Key key;
	Action action;
};


Input::Input( Key k, Action a )
:	key    { k }
,	action { a }
{}


}

}


#endif // WRAP_INPUT_H_
