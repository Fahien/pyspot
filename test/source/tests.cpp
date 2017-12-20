#include "tests.h"
#include "PySpot.h"
#include "PySpotException.h"
#include "PySpotTuple.h"
#include "PyspotExtension.h"
#include "PySpotString.h"
#include "SingleComponent.h"
#include "StringComponent.h"
#include "TestComponent.h"


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
	pst::PySpot pyspot{ "pyspot", PyInit_PySpot };
	pst::PySpotModule pymodule{ pyspot.ImportModule("script") };

	PyTypeObject* type = &singleComponent;

	if (PyType_Ready(type) < 0)
	{
		return false;
	}

	pst::PySpotObject component{ SingleComponent_New(&singleComponent, nullptr, nullptr) };

	pst::PySpotTuple arguments{ 1 };

	pst::PySpotObject num{ Py_BuildValue("f", 4.0f) };
	arguments.SetItem(0, num);

	SingleComponent_Init(reinterpret_cast<SingleComponent*>(component.GetObject()), arguments.GetObject(), nullptr);

	printf("Test3: test_singlecomponent\n");
	pst::PySpotTuple args{ 1 };
	args.SetItem(0, component);
	pymodule.CallFunction("test_singlecomponent", args);

	SingleComponent* comp{ reinterpret_cast<SingleComponent*>(component.GetObject()) };
	printf("Result: %f\n", comp->price);
	return true;
}


bool testStringComponent()
{
	pst::PySpot pyspot{ "pyspot", PyInit_PySpot };
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
	pst::PySpot pyspot{ "pyspot", PyInit_PySpot };
	pst::PySpotModule pymodule{ pyspot.ImportModule("script") };

	PyTypeObject* type = &testComponent;

	if (PyType_Ready(type) < 0)
	{
		return false;
	}

	pst::PySpotObject component{ TestComponent_New(&testComponent, nullptr, nullptr) };

	pst::PySpotTuple arguments{ 2 };

	pst::PySpotObject value{ Py_BuildValue("(i)", 2) };
	arguments.SetItem(0, value);
	pst::PySpotObject price{ Py_BuildValue("(f)", 4.0f) };
	arguments.SetItem(1, price);

	TestComponent_Init(
		reinterpret_cast<TestComponent*>(component.GetObject()),
		arguments.GetObject(),
		nullptr);

	pst::PySpotTuple args{ 1 };
	args.SetItem(0, component);

	printf("Test3: test_component\n");
	pymodule.CallFunction("test_component", args);

	TestComponent* comp{ reinterpret_cast<TestComponent*>(component.GetObject()) };
	printf("Result: %d\n", comp->value);
	return true;
}