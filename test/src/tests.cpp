#include "tests.h"
#include "pyspot/Interpreter.h"
#include "pyspot/Exception.h"
#include "pyspot/Tuple.h"
#include "pyspot/String.h"
#include "pyspot/Dictionary.h"
#include "pytest/extension/Pytest.h"
#include "pytest/component/Single.h"
#include "pytest/component/String.h"
#include "pytest/component/Test.h"
#include "pytest/component/Transform.h"
#include "pytest/input/Input.h"
#include "pytest/input/Key.h"
#include "pytest/input/Action.h"


using namespace pyspot;
using namespace pytest;


bool testHello()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("hello") };
	try
	{
		Object result{ pymodule.CallFunction("hello") };
		printf("Test Hello result = %ls\n", result.ToString().c_str());
	}
	catch (const Exception& ex)
	{
		printf("Error: %s\n", ex.what());
	}
	return true;
}


bool test2()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest };
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
	Interpreter interpreter{ "pytest", PyInit_Pytest };
	Module pymodule{ interpreter.ImportModule("hello") };

	String name{ "TestArg" };
	Tuple arguments{ name };

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
	Interpreter interpreter{ "pytest", PyInit_Pytest, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("script") };

	component::Single single{ 4.0f };
	Tuple args{ single };
	pymodule.CallFunction("test_single", args);
	printf("Result: %f\n", single.GetPrice());
	return true;
}


bool testString()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("script") };

	String name{ "TestName" };
	component::String container{ name };

	printf("Name: %ls\n", name.ToCString());

	printf("Test3: test_string\n");
	Tuple args{ container };
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
	Interpreter interpreter{ "pytest", PyInit_Pytest, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("script") };

	component::Test test{ 2, 4.0f };
	Tuple args{ test };
	pymodule.CallFunction("test_component", args);
	printf("Result: %d\n", test.GetValue());
	return true;
}


bool testTransform()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("script") };

	component::Transform transform{};
	Tuple args{ transform };
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


bool testInput()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, L"/test/script" };
	Module pymodule{ interpreter.ImportModule("script") };

	input::Key k{ input::Key::LEFT };
	input::Action a{ input::Action::RELEASE };
	input::Input i{ k, a };
	Tuple args{ i };
	pymodule.CallFunction("test_input", args);
	return true;
}


bool testMap()
{
	Interpreter interpreter{ "import/Map", PyInit_Pytest, L"/test/script" };
	Module module{ interpreter.ImportModule("map") };
	
	component::Transform transform{};
	Tuple args{ transform };

	module.CallFunction("init_map", args);
	printf("Position: [%f, %f, %f]\n",
	       transform.GetPosition().GetX(),
	       transform.GetPosition().GetY(),
	       transform.GetPosition().GetZ()
	);

	module.CallFunction("test_map");
	printf("Position: [%f, %f, %f]\n",
	       transform.GetPosition().GetX(),
	       transform.GetPosition().GetY(),
	       transform.GetPosition().GetZ()
	);

	return true;
}


bool testDictionary()
{
	Interpreter interpreter{ "import/Map", PyInit_Pytest, L"/test/script" };
	Module module{ interpreter.ImportModule("map") };

	component::Transform transform{};
	Dictionary dict{};
	dict.SetItem("transform", transform);

	Tuple args{ dict };
	module.CallFunction("init_dict", args);
	printf("Position: [%f, %f, %f]\n",
	       transform.GetPosition().GetX(),
	       transform.GetPosition().GetY(),
	       transform.GetPosition().GetZ()
	);

	module.CallFunction("test_dict");
	printf("Position: [%f, %f, %f]\n",
	       transform.GetPosition().GetX(),
	       transform.GetPosition().GetY(),
	       transform.GetPosition().GetZ()
	);

	return true;
}
