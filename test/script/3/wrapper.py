#!/usr/bin/python
import pyspot


def test_test(obj):
	obj.value = 3.0
	obj.cname = "Dent"
	obj.name  = "Prefect"
	obj.person.name = "McMillian"

	person = pyspot.Person(name="Zaphod")
	return pyspot.Test(2.0, "Deep", "Mind", person)


def test_person(person):
	person.name = "Antonio"