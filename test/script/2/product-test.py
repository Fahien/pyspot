import pyspot


def discount_apple(product):
	if product.name == "apple" and not product.discounted:
		product.price -= 1.0
		product.discounted = True
