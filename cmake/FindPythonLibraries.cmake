# Find Python Libraries
message(STATUS "Finding Python ${PYTHON_VERSION}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
	set(PYTHON_NAME python)
	if(NOT TARGET ${PYTHON_NAME})
		add_library(${PYTHON_NAME} SHARED IMPORTED)
		set_target_properties(${PYTHON_NAME} PROPERTIES
			IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libpython${PYTHON_VERSION}.so)
	endif()

	set(PYTHON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/pyspot/android/python${PYTHON_VERSION})
	set(PYTHON_LIBRARIES ${PYTHON_NAME})
elseif(UNIX)
	set(PYTHON_NAME python)
	if(NOT TARGET ${PYTHON_NAME})
		add_library(${PYTHON_NAME} SHARED IMPORTED)
		set_target_properties(${PYTHON_NAME} PROPERTIES
			IMPORTED_LOCATION /usr/lib/python${PYTHON_VERSION}/config-x86_64-linux-gnu/libpython${PYTHON_VERSION}.so)
	endif()

	set(PYTHON_INCLUDE_DIR /usr/include/python${PYTHON_VERSION})
	set(PYTHON_LIBRARIES ${PYTHON_NAME})
else()
	if(${PYTHON_VERSION} MATCHES "3")
		find_package(PythonLibs ${PYTHON_VERSION})
	else()
		set(PYTHON_NAME python)
		if(NOT TARGET ${PYTHON_NAME})
			add_library(${PYTHON_NAME} STATIC IMPORTED)
			set_target_properties(${PYTHON_NAME} PROPERTIES
				IMPORTED_LOCATION "$ENV{PYTHON27_PATH}/libs/python27.lib")
			message(STATUS "Found PythonLibraries: $ENV{PYTHON27_PATH}")
		endif()

		set(PYTHON_INCLUDE_DIR "$ENV{PYTHON27_PATH}/include")
		set(PYTHON_LIBRARIES ${PYTHON_NAME})
	endif()
endif()
