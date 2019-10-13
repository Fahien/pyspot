#pragma once

#include <catch2/catch.hpp>
#include <pyspot/Bindings.h>
#include <pyspot/Extension.h>
#include <pyspot/Interpreter.h>
#include <pyspot/Module.h>
#include <pyspot/Wrapper.h>

namespace pyspot::test
{


static pyspot::Interpreter& get_interpreter()
{
	static pyspot::Interpreter interpreter{ "pyspot", PyInit_pyspot, L"script" };
	return interpreter;
}


}  // namespace pyspot::test
