#ifndef PYSPOT_TEST_TEST_H_
#define PYSPOT_TEST_TEST_H_

#include <gtest/gtest.h>
#include <pyspot/Bindings.h>
#include <pyspot/Extension.h>
#include <pyspot/Interpreter.h>
#include <pyspot/Module.h>
#include <pyspot/Wrapper.h>

namespace pyspot
{
namespace test
{
static pyspot::Interpreter& get_interpreter()
{
	static pyspot::Interpreter interpreter{ "pyspot", PyInit_pyspot, L"script" };
	return interpreter;
}

class Python : public testing::Test
{
  public:
	inline Python();
	void SetUp() override{};
	void TearDown() override{};

  private:
	pyspot::Interpreter& interpreter;
};

Python::Python() : interpreter{ get_interpreter() } {}


}  // namespace test
}  // namespace pyspot

#endif  // PYSPOT_TEST_TEST_H_
