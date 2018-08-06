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
	person = pyspot.Person( name="Zaphod" )
	return pyspot.Test( 1, 2.0, "Deep", "Thought", person )
