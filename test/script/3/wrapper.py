#!/usr/bin/python
import pyspot


def modify_member_int( obj ):
	obj.index = 1


def modify_member_float( obj ):
	obj.value = 1.0


def modify_member_cstring( obj ):
	obj.cname = "Dent"


def modify_member_string( obj ):
	obj.name = "Prefect"


def call_method_with_arg( obj ):
	obj.SetValue( 1.0 )


def get_method_return_value( obj ):
	obj.person.name = obj.GetNames()


def get_created_object():
	person = pyspot.Person( n="Zaphod" )
	return pyspot.Test( 1, 2.0, "Deep", "Thought", person )


def compare_enums(inp):
	print(dir(pyspot.Key))

	if inp.key == pyspot.Key.UP:
		inp.key = pyspot.Key.RIGHT

	if inp.action == pyspot.Action.PRESS:
		inp.action = pyspot.Action.RELEASE
