import pyspot


def create_origin():
	return pyspot.test.Vec2[int]()


def create_one():
	one = pyspot.test.Vec2[float]()
	one.x = 1.0
	one.y = 1.0
	return one


def move_origin( a ):
	a.x = 1.0
	a.y = 2.0
