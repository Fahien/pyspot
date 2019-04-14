import pyspot


def create_color():
	print(dir(pyspot))
	print(dir(pyspot.test))
	color = pyspot.test.Color.RED
	return color


def send_color( color ):
	return color


def compare_color( color ):
	return color == pyspot.test.Color.GREEN


def change_color( color ):
	color = pyspot.test.Color.RED
	return color
