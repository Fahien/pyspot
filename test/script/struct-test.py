import pyspot


def create_details():
	details = pyspot.test.Details(1)
	return details


def send_details( details ):
	return details


def compare_details( details ):
	return details == pyspot.test.Details(3)


def change_details( details ):
	details = pyspot.test.Details(6)
	return details
