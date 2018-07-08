#!/usr/bin/python
import pytest

def hello():
	print('Hello from Python')

	try:
		pytest.invoke()
		print('Pytest Invoked')
	except Exception as ex:
		print('Exception %s' % ex)

	return 'All right'


def readargs(a):
	print('Reading a: %s' % a)
	a = 'ModifiedTestArg'
	return 'Done'