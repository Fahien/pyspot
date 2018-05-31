#include "tests.h"
#include "pyspot/Interpreter.h"
#include "pyspot/Exception.h"
#include "pyspot/Tuple.h"
#include "pyspot/String.h"
#include "pyspot/extension/Extension.h"
#include "pyspot/component/Single.h"
#include "pyspot/component/String.h"
#include "pyspot/component/Test.h"
#include "pyspot/component/Transform.h"


using namespace pyspot;


bool test1()
{
	Interpreter interpreter{};
	Module pymodule{ interpreter.ImportModule("hello") };
	try
	{
		Object result{ pymodule.CallFunction("hello") };
		printf("Test 1 result = %ls\n", result.ToString().c_str());
	}
	catch (const Exception & ex)
	{
		printf("Error: %s\n", ex.what());
	}
	return true;
}


bool test2()
{
	Interpreter interpreter{ "pyspot", PyInit_PySpot };
	Module pymodule{ interpreter.ImportModule("hello") };
	try
	{
		Object result{ pymodule.CallFunction("hello") };
		printf("Test 2 result = %ls\n", result.ToString().c_str());
	}
	catch (const Exception & ex)
	{
		printf("Error correctly captured: %s\n", ex.what());
	}
	return true;
}


bool testArgs()
{
	Interpreter interpreter{ "pyspot", PyInit_PySpot };
	Module pymodule{ interpreter.ImportModule("hello") };

	Tuple arguments{ 1 };

	String name{ "TestArg" };
	arguments.SetItem(0, name);

	try
	{
		Object result{ pymodule.CallFunction("readargs", arguments) };
		printf("Test Arg result = %ls\n", result.ToString().c_str());
		printf("Test Arg name = %ls\n", name.ToString().c_str());
	}
	catch (const Exception & ex)
	{
		printf("Error correctly captured: %s\n", ex.what());
	}
	return true;
}


bool testSingle()
{
	Interpreter interpreter{ "pyspot", PyInit_PySpot, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("script") };

	component::Single single{ 4.0f };
	Tuple args{ &single };
	pymodule.CallFunction("test_single", args);
	printf("Result: %f\n", single.GetPrice());
	return true;
}


bool testString()
{
	Interpreter interpreter{ "pyspot", PyInit_PySpot, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("script") };

	String name{ "TestName" };
	component::String container{ name };

	printf("Name: %ls\n", name.ToCString());

	printf("Test3: test_string\n");
	Tuple args{ &container };
	try
	{
		pymodule.CallFunction("test_string", args);
		printf("Result: %ls\n", container.GetName().ToCString());
	}
	catch (const Exception & ex)
	{
		printf("Error correctly captured: %s\n", ex.what());
	}

	return true;
}


bool testTest()
{
	Interpreter interpreter{ "pyspot", PyInit_PySpot, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("script") };

	component::Test test{ 2, 4.0f };
	Tuple args{ &test };
	pymodule.CallFunction("test_component", args);
	printf("Result: %d\n", test.GetValue());
	return true;
}


bool testTransform()
{
	Interpreter interpreter{ "pyspot", PyInit_PySpot, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("script") };

	component::Transform transform{};
	Tuple args{ &transform };
	pymodule.CallFunction("test_transform", args);
	printf("Position: [%f, %f, %f]\n",
	       transform.GetPosition().GetX(),
	       transform.GetPosition().GetY(),
	       transform.GetPosition().GetZ()
	);
	printf("Scale: [%f, %f, %f]\n",
	       transform.GetScale().GetX(),
	       transform.GetScale().GetY(),
	       transform.GetScale().GetZ()
	);
	printf("Rotation: [%f, %f, %f]\n",
	       transform.GetRotation().GetX(),
	       transform.GetRotation().GetY(),
	       transform.GetRotation().GetZ()
	);
	return true;
}