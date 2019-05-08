import pyspot


def create_orange():
	return pyspot.test.Product( "Orange", 1.0 )


def discount_apple(product):
	if product.name == "Apple" and not product.discounted:
		product.price -= 1.0
		product.discounted = True
