#!/usr/bin/python
import pyspot


def test_singlecomponent(c):
	print('PySpot module: ', end='')
	print(dir(pyspot))

	try:
		print('Creating SingleComponent')
		a = pyspot.SingleComponent(1.0)
		print(dir(a))
		print("a.price: ", a.price)
		print("c.price: ", c.price)
		c.price = 2.0

	except Exception as ex:
		print('Exception captured: ', str(ex))
	except:
		print('Exception captured')


def test_stringcomponent(c):
	print('PySpot module: ', end='')
	print(dir(pyspot))

	try:
		print('Creating StringComponent')
		a = pyspot.StringComponent("PythonName")
		print(dir(a))
		print("a.name: ", a.name)
		print("c.name: ", c.name)
		c.name = "ModifiedName"

	except Exception as ex:
		print('Exception captured: ', str(ex))
	except:
		print('Exception captured')


def test_component(b):
	print('PySpot module: ', end='')
	print(dir(pyspot))

	print('Invoking PySpot')
	try:
		pyspot.invoke()
		print('PySpot invoked')

		print('Creating TestComponent')
		component = pyspot.TestComponent(1, 2.0)
		print(dir(component))
		print("component.value", component.value)
		print("component.price", component.price)
		b.value = 2
		b.price = 4.0
		print("b.value = ", b.value)
		print("b.price = ", b.price)

	except Exception as ex:
		print('Exception captured: ', str(ex))
	except:
		print('Exception captured')

