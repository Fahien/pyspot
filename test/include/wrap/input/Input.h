#ifndef WRAP_INPUT_H_
#define WRAP_INPUT_H_


namespace wrap
{

namespace input
{


enum class [[pyspot::export]] Key
{
	UP    = 0,
	LEFT  = 1,
	DOWN  = 2,
	RIGHT = 3,
};


enum class [[pyspot::export]] Action
{
	RELEASE = 0,
	PRESS   = 1,
};


class [[pyspot::export]] Input
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


} // namespace input

} // namespace wrap


#endif // WRAP_INPUT_H_
