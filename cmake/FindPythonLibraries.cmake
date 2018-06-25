# Find Python Libraries
if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
	set(PYTHON_NAME python2)
	if(NOT TARGET ${PYTHON_NAME})
		add_library(${PYTHON_NAME} SHARED IMPORTED)
		set_target_properties(${PYTHON_NAME} PROPERTIES
			IMPORTED_LOCATION libpython2.7.so)
	endif()

	set(PYTHON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/python2.7)
	set(PYTHON_LIBRARIES ${PYTHON_NAME})
elseif(UNIX)
	set(PYTHON_NAME python2)
	if(NOT TARGET ${PYTHON_NAME})
		add_library(${PYTHON_NAME} SHARED IMPORTED)
		set_target_properties(${PYTHON_NAME} PROPERTIES
			IMPORTED_LOCATION /usr/lib/python2.7/config-x86_64-linux-gnu/libpython2.7.so)
	endif()

	set(PYTHON_INCLUDE_DIR /usr/include/python2.7)
	set(PYTHON_LIBRARIES ${PYTHON_NAME})
else()
	find_package(PythonLibs EXACT 2.7)
endif()
