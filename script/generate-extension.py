"""This script generates a PySpot Extension"""

import os
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


def prepare_source(extension_dir, name, methods, components):
	"""Prepares dictionary template for the source"""
	dictionary = prepare_header(name)
	dictionary['methods']    = methods
	dictionary['components'] = []

	for component_name in components:
		try:
			component_path = "%s/%s.json" % (extension_dir, component_name.replace('::', '/'))
			with open(component_path) as json_data:
				component = json.load(json_data)
				dictionary['components'].append(component)
		except:
			FileNotFoundError('Cannot load component: %s not found' % component_name)

	return dictionary


def render_template(template_name, dictionary, out_path=None):
	"""Renders a template using a dictionary"""
	try:
		with open(template_name) as template_file:
			template = Template(template_file.read())
	except FileNotFoundError:
		exit('Cannot render template: %s not found' % template_name)

	code = template.render(dictionary)

	if out_path != None:
		# Write to file
		parent_path = os.path.dirname(out_path)
		if not os.path.exists(parent_path):
			os.makedirs(parent_path)
		with open(out_path, "w") as out:
			out.write(code)
	else:
		# Write to std output
		print(code)


def create_header(name, out_path=None):
	"""Creates the Extension header"""
	dictionary = prepare_header(name)
	render_template('Extension.template.h', dictionary, out_path)


def create_source(extension_dir, name, methods, components, out_path=None):
	"""Creates the Extension source"""
	dictionary = prepare_source(extension_dir, name, methods, components)
	render_template('Extension.template.cpp', dictionary, out_path)


def main():
	"""Entry point"""
	if len(sys.argv) < 2:
		exit('Usage: %s extension.json [-h] [<output path>]' % sys.argv[0])

	# Get the json path
	extension = sys.argv[1]
	extension_dir = os.path.dirname(extension)

	# Read the json file
	try:
		with open(extension) as json_data:
			data = json.load(json_data)
	except FileNotFoundError:
		exit('Cannot generate PySpot extension: %s not found' % extension)

	name = data['name']

	# Check the header switch
	if len(sys.argv) >= 3 and sys.argv[2] == '-h':
		if len(sys.argv) == 4:
			output_path = sys.argv[3]
		create_header(name, output_path)
	else:
		if len(sys.argv) == 3:
			output_path = sys.argv[2]
		methods    = data['methods']
		components = data['components']
		create_source(extension_dir, name, methods, components, output_path)


main()
