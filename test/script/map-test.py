import pyspot


def create_week():
	week = pyspot.test.Week()
	if week.days[1] == "monday":
		return week
	else:
		return None


def modify_monday( week ):
	days = week.days
	days[1] = "tuesday"
	week.days = days
