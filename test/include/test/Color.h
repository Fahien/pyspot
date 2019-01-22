#ifndef PYSPOT_TEST_COLOR_H_
#define PYSPOT_TEST_COLOR_H_


namespace pyspot
{
namespace test
{

	
class [[pyspot::export]] Coin
{
  public:
	int value;
};
enum class [[pyspot::export]] Color
{
	RED, GREEN, BLUE
};


} // namespace test
} // namespace pyspot


#endif // PYSPOT_TEST_COLOR_H_
