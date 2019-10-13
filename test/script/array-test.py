import pyspot


def create_week():
	week = pyspot.test.Week()
	if week.day_numbers[0] == 1:
		return week
	else:
		return None


def increase_monday( week ):
	days = week.day_numbers
	days[0] = 2
	week.day_numbers = days
