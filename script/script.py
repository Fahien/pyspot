#!/usr/bin/python
import pytest


def test_function():
	print('PyTest module: ', end='')
	print(dir(pytest))

	print('Invoking PyTest')
	try:
		pytest.invoke()
	except Exception as ex:
		print('Exception captured: ', str(ex))

	print('PyTest invoked')
