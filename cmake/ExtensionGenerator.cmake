# Generate the Extension sources
macro(generate_extension EXT_DIR EXT_NAME)

	string(TOLOWER ${EXT_NAME} EXT_LNAME)
	set(EXT_PATH ${EXT_DIR}/${EXT_LNAME})
	set(EXT_JSON ${EXT_PATH}/${EXT_NAME}.json)
	set(EXTENSION_HEADER  ${CMAKE_CURRENT_BINARY_DIR}/include/${EXT_LNAME}/extension/${EXT_NAME}.h)
	set(EXTENSION_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/src/${EXT_LNAME}/extension/${EXT_NAME}.cpp)
	set(EXTENSION_SOURCES ${EXTENSION_HEADER} ${EXTENSION_SOURCE})

	# Get all the folders under extension/name
	file(GLOB NAMESPACES LIST_DIRECTORY true ${EXT_PATH}/*)
	foreach(NAMESPACE ${NAMESPACES})
		if(IS_DIRECTORY ${NAMESPACE})
			# Get all the jsons
			file(GLOB COMPONENTS ${NAMESPACE}/*json)
			foreach(COMPONENT ${COMPONENTS})
				get_filename_component(NAMESPACE_NAME ${NAMESPACE} NAME_WE)
				get_filename_component(CLASS_NAME ${COMPONENT} NAME_WE)
				set(CLASS_HEADER ${CMAKE_CURRENT_BINARY_DIR}/include/${EXT_LNAME}/${NAMESPACE_NAME}/${CLASS_NAME}.h)
				list(APPEND EXTENSION_SOURCES ${CLASS_HEADER})
			endforeach()
		endif()
	endforeach()

	add_custom_command(
		OUTPUT ${EXTENSION_HEADER} ${EXTENSION_SOURCE}
		COMMAND ${PYTHON_EXECUTABLE} genextension.py ${PYTHON_VERSION} ${EXT_JSON} -h ${EXTENSION_HEADER}
		COMMAND ${PYTHON_EXECUTABLE} genextension.py ${PYTHON_VERSION} ${EXT_JSON} ${EXTENSION_SOURCE}
		WORKING_DIRECTORY ${PST_SCRIPT_DIR}
		COMMENT "Generating ${EXTENSION}"
		VERBATIM)

endmacro(generate_extension)