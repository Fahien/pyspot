#include "tests.h"
#include "PySpot.h"
#include "PySpotException.h"
#include "PySpotTuple.h"
#include "PyspotExtension.h"
#include "PySpotString.h"
#include "SingleComponent.h"
#include "StringComponent.h"
#include "TestComponent.h"
#include "TransformComponent.h"


namespace pst = pyspot;


bool test1()
{
	pst::PySpot pyspot{};
	pst::PySpotModule pymodule{ pyspot.ImportModule("hello") };
	try
	{
		pst::PySpotObject result{ pymodule.CallFunction("hello") };
		printf("Test 1 result = %ls\n", result.ToString().c_str());
	}
	catch (const pst::PySpotException & ex)
	{
		printf("Error: %s\n", ex.what());
	}
	return true;
}


bool test2()
{
	pst::PySpot pyspot{ "pyspot", PyInit_PySpot };
	pst::PySpotModule pymodule{ pyspot.ImportModule("hello") };
	try
	{
		pst::PySpotObject result{ pymodule.CallFunction("hello") };
		printf("Test 2 result = %ls\n", result.ToString().c_str());
	}
	catch (const pst::PySpotException & ex)
	{
		printf("Error correctly captured: %s\n", ex.what());
	}
	return true;
}


bool testArgs()
{
	pst::PySpot pyspot{ "pyspot", PyInit_PySpot };
	pst::PySpotModule pymodule{ pyspot.ImportModule("hello") };

	pst::PySpotTuple arguments{ 1 };

	pst::PySpotString name{ "TestArg" };
	arguments.SetItem(0, name);

	try
	{
		pst::PySpotObject result{ pymodule.CallFunction("readargs", arguments) };
		printf("Test Arg result = %ls\n", result.ToString().c_str());
		printf("Test Arg name = %ls\n", name.ToString().c_str());
	}
	catch (const pst::PySpotException & ex)
	{
		printf("Error correctly captured: %s\n", ex.what());
	}
	return true;
}


bool testSingleComponent()
{
	pst::PySpot pyspot{ "pyspot", PyInit_PySpot, L"/test/script" };
	pst::PySpotModule pymodule{ pyspot.ImportModule("script") };

	PySpotSingleComponent singleComponent{ 4.0f };
	pst::PySpotTuple args{ &singleComponent };
	pymodule.CallFunction("test_singlecomponent", args);
	printf("Result: %f\n", singleComponent.GetPrice());
	return true;
}


bool testStringComponent()
{
	pst::PySpot pyspot{ "pyspot", PyInit_PySpot, L"/test/script" };
	pst::PySpotModule pymodule{ pyspot.ImportModule("script") };

	pst::PySpotString name{ "TestName" };
	PySpotStringComponent container{ name };

	printf("Name: %ls\n", name.ToCString());

	printf("Test3: test_stringcomponent\n");
	pst::PySpotTuple args{ &container };
	try
	{
		pymodule.CallFunction("test_stringcomponent", args);
		printf("Result: %ls\n", container.GetName().ToCString());
	}
	catch (const pst::PySpotException & ex)
	{
		printf("Error correctly captured: %s\n", ex.what());
	}

	return true;
}


bool testTestComponent()
{
	pst::PySpot pyspot{ "pyspot", PyInit_PySpot, L"/test/script" };
	pst::PySpotModule pymodule{ pyspot.ImportModule("script") };

	PySpotTestComponent testComponent{ 2, 4.0f };
	pst::PySpotTuple args{ &testComponent };
	pymodule.CallFunction("test_component", args);
	printf("Result: %d\n", testComponent.GetValue());
	return true;
}


bool testTransformComponent()
{
	pst::PySpot pyspot{ "pyspot", PyInit_PySpot, L"/test/script" };
	pst::PySpotModule pymodule{ pyspot.ImportModule("script") };

	PySpotTransformComponent transform{};
	pst::PySpotTuple args{ &transform };
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
