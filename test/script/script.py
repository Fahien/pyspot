#!/usr/bin/python
import pytest


def test_single(c):
	print('Pytest module: ', end='')
	print(dir(pytest))

	try:
		print('Creating Single')
		a = pytest.Single(1.0)
		print(dir(a))
		print("a.price: ", a.price)
		print("c.price: ", c.price)
		c.price = 2.0

	except Exception as ex:
		print('Exception captured: ', str(ex))
	except:
		print('Exception captured')


def test_string(c):
	print('Pytest module: ', end='')
	print(dir(pytest))

	try:
		print('Creating String')
		a = pytest.String("PythonName")
		print(dir(a))
		print("a.name: ", a.name)
		print("c.name: ", c.name)
		c.name = "ModifiedName"

	except Exception as ex:
		print('Exception captured: ', str(ex))
	except:
		print('Exception captured')


def test_component(b):
	print('Pytest module: ', end='')
	print(dir(pytest))

	print('Invoking Pytest')
	try:
		pytest.invoke()
		print('Pytest invoked')

		print('Creating Test')
		component = pytest.Test(1, 2.0)
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
	print('Pytest module: ', end='')
	print(dir(pytest))
	
	try:
		print('Creating String')
		a = pytest.Transform()
		print(dir(a))
		print("a.position: ", a.position)
		print("a.scale: ",    a.scale)
		print("a.rotation: ", a.rotation)
		transform.position.x = 1.0

	except Exception as ex:
		print('Exception captured: ', str(ex))
	except:
		print('Exception captured')


def test_input(input):
	if (input.key == pytest.Key.LEFT):
		if (input.action == pytest.Action.RELEASE):
			print('Key LEFT Pressed')
	else:
		print('Wrong input')
