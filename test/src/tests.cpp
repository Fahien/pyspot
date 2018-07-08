#include "tests.h"
#include "pyspot/Interpreter.h"
#include "pyspot/Module.h"
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

#include <iostream>

using namespace std;
using namespace pyspot;
using namespace pytest;

#if PYTHON_VERSION >= 3
# define TEST_DIR _T("test/script/3")
#else
# define TEST_DIR _T("test/script/2")
#endif


bool testHello()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, TEST_DIR };
	Module pymodule{ "hello" };
	try
	{
		Object result{ pymodule.Invoke("hello") };
		printf("Test Hello result = %s\n", result.ToTString().c_str());
	}
	catch (const Exception& ex)
	{
		printf("Error: %s\n", ex.what());
	}
	return true;
}


bool testArgs()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest };
	Module pymodule{ "hello" };

	String name{ "TestArg" };
	Tuple arguments{ name };

	try
	{
		Object result{ pymodule.Invoke("readargs", arguments) };
		printf("Test Arg result = %s\n", result.ToTString().c_str());
		printf("Test Arg name = %s\n", name.ToTString().c_str());
	}
	catch (const Exception & ex)
	{
		printf("Error correctly captured: %s\n", ex.what());
	}
	return true;
}


bool testSingle()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, TEST_DIR };
	printf("Interpreter..");
	Module pymodule{ "script" };
	printf("Module..");

	component::Single single{ 4.0f };
	printf("Single..");
	Tuple args{ single };
	printf("Tuple..");
	pymodule.Invoke("test_single", args);
	printf("Result: %f\n", single.GetPrice());
	return true;
}


bool testString()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, TEST_DIR };
	try
	{
		Module pymodule{ "script" };

		String name{ "TestName" };
		component::String container{ name };

		printf("Name: %s\n", name.ToCString());

		printf("Test3: test_string\n");
		Tuple args{ container };
		try
		{
			pymodule.Invoke("test_string", args);
			printf("Result: %s\n", container.GetName().ToCString());
		}
		catch (const Exception & ex)
		{
			printf("Error correctly captured: %s\n", ex.what());
		}
	}
	catch(Exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return true;
}


bool testTest()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, TEST_DIR };
	Module pymodule{ "script" };

	component::Test test{ 2, 4.0f };
	Tuple args{ test };
	pymodule.Invoke("test_component", args);
	printf("Result: %d\n", test.GetValue());
	return true;
}


bool testTransform()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, TEST_DIR };
	Module pymodule{ "script" };

	component::Transform transform{};
	Tuple args{ transform };
	pymodule.Invoke("test_transform", args);
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
	Interpreter interpreter{ "pytest", PyInit_Pytest, TEST_DIR };
	Module pymodule{ "script" };

	input::Key k{ input::Key::LEFT };
	input::Action a{ input::Action::RELEASE };
	input::Input i{ k, a };
	Tuple args{ i };
	pymodule.Invoke("test_input", args);
	return true;
}


bool testMap()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, TEST_DIR };
	Module module{ "map" };
	
	component::Transform transform{};
	Tuple args{ transform };

	module.Invoke("init_map", args);
	printf("Position: [%f, %f, %f]\n",
	       transform.GetPosition().GetX(),
	       transform.GetPosition().GetY(),
	       transform.GetPosition().GetZ()
	);

	module.Invoke("test_map");
	printf("Position: [%f, %f, %f]\n",
	       transform.GetPosition().GetX(),
	       transform.GetPosition().GetY(),
	       transform.GetPosition().GetZ()
	);

	return true;
}


bool testDictionary()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, TEST_DIR };
	Module module{ "map" };

	component::Transform transform{};
	Dictionary dict{};
	dict.SetItem("transform", transform);

	Tuple args{ dict };
	module.Invoke("init_dict", args);
	printf("Position: [%f, %f, %f]\n",
	       transform.GetPosition().GetX(),
	       transform.GetPosition().GetY(),
	       transform.GetPosition().GetZ()
	);

	module.Invoke("test_dict");
	printf("Position: [%f, %f, %f]\n",
	       transform.GetPosition().GetX(),
	       transform.GetPosition().GetY(),
	       transform.GetPosition().GetZ()
	);

	return true;
}


bool testBuildCustomPythonObject()
{
	Interpreter interpreter{ "pytest", PyInit_Pytest, TEST_DIR };

	// Create a utils.Map
	Module utils{ "utils" };
	Dictionary map{ utils.Invoke("Map") };
	assert(map.GetObject() != nullptr);

	// Add a transform
	component::Transform transform;
	map.SetItem("transform", transform);

	// Modify within script
	Module module{ "map" };
	module.Invoke("test_parameter", Tuple{ map });

	cout << transform.GetPosition().GetX() << endl;
	assert(transform.GetPosition().GetX() == 1.0f);

	return true;
}