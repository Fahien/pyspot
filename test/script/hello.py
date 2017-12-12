#!/usr/bin/python
import pyspot

def hello():
	print('Hello from Python')

	try:
		pyspot.invoke()
		print('Pyspot Invoked')
	except Exception as ex:
		print('Exception %s' % ex)

	return 'All right'


def readargs(a):
	print('Reading a: %s' % a)
	a = 'ModifiedTestArg'
	return 'Done'