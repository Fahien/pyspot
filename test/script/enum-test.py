import pyspot


def create_color():
	color = pyspot.Color.RED
	return color


def send_color( color ):
	return color


def compare_color( color ):
	return color == pyspot.Color.GREEN


def change_color( color ):
	color = pyspot.Color.RED
	return color
