#!/usr/bin/python
import pytest
import data

entity = data.Map()

def init_map(transform):
	transform.position.x = 1.0
	entity.transform = transform


def test_map():
	entity.transform.position.x = 2.0


dictionary = data.Map()

def init_dict(components):
	dictionary.update(components)
	dictionary.transform.position.x = 3.0

def test_dict():
	dictionary.transform.position.x = 4.0
