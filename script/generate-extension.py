"""This script generates a PySpot Extension"""

import sys
import json
from jinja2 import Template


def prepare_header(name):
	"""Prepares dictionary template for the header"""
	return {
		'extension': name.lower(),
		'Extension': name.lower().capitalize(),
		'EXTENSION': name.upper()
	}


def prepare_source(name, methods, components):
	"""Prepares dictionary template for the source"""
	dictionary = prepare_header(name)
	dictionary['methods']    = methods
	dictionary['components'] = components
	return dictionary


def render_template(template_name, dictionary):
	"""Renders a template using a dictionary"""
	try:
		with open(template_name) as template_file:
			template = Template(template_file.read())
	except FileNotFoundError:
		exit('Cannot render template: %s not found' % template_name)
	print(template.render(dictionary))


def create_header(name):
	"""Creates the Extension header"""
	render_template('Extension.template.h', prepare_header(name))


def create_source(name, methods, components):
	"""Creates the Extension source"""
	render_template('Extension.template.cpp', prepare_source(name, methods, components))


def main():
	"""Entry point"""
	if len(sys.argv) < 2:
		exit('Usage: %s extension.json [-h]' % sys.argv[0])

	# Get the json path
	extension = sys.argv[1]

	# Read the json file
	try:
		with open(extension) as json_data:
			data = json.load(json_data)
	except FileNotFoundError:
		exit('Cannot generate PySpot extension: %s not found' % extension)

	name = data['name']

	# Check the header switch
	if len(sys.argv) == 3 and sys.argv[2] == '-h':
		create_header(name)
	else:
		methods    = data['methods']
		components = data['components']
		create_source(name, methods, components)


main()
