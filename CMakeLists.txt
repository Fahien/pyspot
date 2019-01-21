cmake_minimum_required( VERSION 3.6 )

set(CMAKE_C_STANDARD 11)

set(PST_TITLE PySpot)
set(PST_NAME  pyspot)
project(${PST_TITLE} C CXX)

# Version number
set(PST_VERSION_MAJOR 0)
set(PST_VERSION_MINOR 7)

# Directories
set(PST_SCRIPT_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/script)
set(PST_SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PST_INCLUDE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PST_GEN_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include)

# Configure a header file to pass some of the CMake settings to the source code
configure_file(${PST_SOURCE_DIR}/Config.h.in ${PST_GEN_INCLUDE_DIR}/Config.h)

# CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(PythonInterp 3)
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register" )
endif()

# Python
if( ${PY_VERSION} MATCHES "2" )
	set( PYTHONLIBS_VERSION_STRING ${PY_VERSION} )
	add_definitions( -DPY_MAJOR_VERSION=2 )
	if(NOT TARGET python )
		add_library( python STATIC IMPORTED )
		set( PYTHON_LIBRARY "$ENV{PYTHON27_PATH}/libs/python27.lib" )
		set( PYTHON_LIBRARY_DEBUG "$ENV{PYTHON27_PATH}/libs/python27_d.lib" )
		set_target_properties( python PROPERTIES
			IMPORTED_LOCATION ${PYTHON_LIBRARY}
			IMPORTED_LOCATION_DEBUG ${PYTHON_LIBRARY_DEBUG})
		message(STATUS "Found PythonLibs: $ENV{PYTHON27_PATH}")
	endif()
	set(PYTHON_INCLUDE_DIRS "$ENV{PYTHON27_PATH}/include")
	set(PYTHON_LIBRARIES python)
else()
	find_package(PythonLibs EXACT ${PY_VERSION})
endif()

set(PST_INCLUDE_DIRS
	${PST_INCLUDE_DIR}
	${PST_GEN_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIRS})

# Sources
set(SOURCES
	${PST_SOURCE_DIR}/Error.cpp
	${PST_SOURCE_DIR}/Interpreter.cpp
	${PST_SOURCE_DIR}/Object.cpp
	${PST_SOURCE_DIR}/Long.cpp
	${PST_SOURCE_DIR}/Bool.cpp
	${PST_SOURCE_DIR}/String.cpp
	${PST_SOURCE_DIR}/Method.cpp
	${PST_SOURCE_DIR}/Module.cpp
	${PST_SOURCE_DIR}/Tuple.cpp
	${PST_SOURCE_DIR}/Dictionary.cpp)
source_group(src FILES ${SOURCES})

# Library
add_library(${PST_NAME} ${SOURCES})
target_link_libraries(${PST_NAME} PUBLIC ${PYTHON_LIBRARIES})
set(PYSPOT_LIBRARIES ${PST_NAME})
target_include_directories(${PST_NAME} PUBLIC ${PST_INCLUDE_DIRS})

add_subdirectory( test )
