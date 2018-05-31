#!/usr/bin/python
import pyspot


def test_single(c):
	print('PySpot module: ', end='')
	print(dir(pyspot))

	try:
		print('Creating Single')
		a = pyspot.Single(1.0)
		print(dir(a))
		print("a.price: ", a.price)
		print("c.price: ", c.price)
		c.price = 2.0

	except Exception as ex:
		print('Exception captured: ', str(ex))
	except:
		print('Exception captured')


def test_string(c):
	print('PySpot module: ', end='')
	print(dir(pyspot))

	try:
		print('Creating String')
		a = pyspot.String("PythonName")
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

		print('Creating Test')
		component = pyspot.Test(1, 2.0)
		print(dir())
		print("c.value", component.value)
		print("c.price", component.price)
		b.value = 2
		b.price = 4.0
		print("b.value = ", b.value)
		print("b.price = ", b.price)

	except Exception as ex:
		print('Exception captured: ', str(ex))
	except:
		print('Exception captured')


def test_transform(transform):
	print('PySpot module: ', end='')
	print(dir(pyspot))
	
	try:
		print('Creating String')
		a = pyspot.Transform()
		print(dir(a))
		print("a.position: ", a.position)
		print("a.scale: ",    a.scale)
		print("a.rotation: ", a.rotation)
		transform.position.x = 1.0

	except Exception as ex:
		print('Exception captured: ', str(ex))
	except:
		print('Exception captured')
