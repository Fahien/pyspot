#ifndef WRAP_INPUT_H_
#define WRAP_INPUT_H_


namespace wrap
{

namespace input
{


enum class Key
{
	UP    = 0,
	LEFT  = 1,
	DOWN  = 2,
	RIGHT = 3,
};


enum class Action
{
	RELEASE = 0,
	PRESS   = 1,
};


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
