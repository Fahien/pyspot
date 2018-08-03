#!/usr/bin/python
import pyspot


def test(obj):
	obj.value = 3.0
	return -obj.value
