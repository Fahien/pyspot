#!/usr/bin/python
import pyspot


def test_test(obj):
	obj.value = 3.0
	return -obj.value


def test_person(person):
	person.name = "Antonio"