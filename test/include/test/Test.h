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


class Python : public testing::Test
{
  public:
	inline Python();
	void SetUp() override{};
	void TearDown() override{};

  private:
	std::unique_ptr<pyspot::Interpreter> interpreter;
};

Python::Python() : interpreter{ new pyspot::Interpreter{ "pyspot", PyInit_pyspot, L"script" } } {}


}  // namespace test
}  // namespace pyspot

#endif  // PYSPOT_TEST_TEST_H_
