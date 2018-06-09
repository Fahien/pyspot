#!/usr/bin/python
import pytest
import data

entity = data.Map()

def init_map(transform):
	transform.position.x = 1.0
	entity.transform = transform


def test_map():
	entity.transform.position.x = 2.0
