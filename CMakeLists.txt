cmake_minimum_required( VERSION 3.6 )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_C_STANDARD 11 )
set( CMAKE_CXX_STANDARD 14 )

set( PST_TITLE PySpot )
set( PST_NAME  pyspot )
project( ${PST_TITLE} C CXX )

# Version number
set( PST_VERSION_MAJOR 0 )
set( PST_VERSION_MINOR 7 )

# Directories
set( PST_SCRIPT_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/script )
set( PST_SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( PST_INCLUDE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( PST_GEN_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include )

# Configure a header file to pass some of the CMake settings to the source code
configure_file( ${PST_SOURCE_DIR}/Config.h.in ${PST_GEN_INCLUDE_DIR}/Config.h )

# CMake modules
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
find_package( PythonInterp 3 )

# Python version default to 2
if( NOT DEFINED ${PY_VERSION} )
	set(PY_VERSION "2.7")
endif()

# Python 2 will be imported
if( ${PY_VERSION} MATCHES "2" )
	if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
		# Ignore warning from python 2
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register" )
	endif()
	set( PYTHONLIBS_VERSION_STRING ${PY_VERSION} )
	add_definitions( -DPY_MAJOR_VERSION=2 )
endif()
find_package( PythonLibs EXACT ${PY_VERSION} )

set( PST_INCLUDE_DIRS
	${PST_INCLUDE_DIR}
	${PST_GEN_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIRS}
)

# Sources
set( SOURCES
	${PST_SOURCE_DIR}/Error.cpp
	${PST_SOURCE_DIR}/Interpreter.cpp
	${PST_SOURCE_DIR}/Object.cpp
	${PST_SOURCE_DIR}/Long.cpp
	${PST_SOURCE_DIR}/Bool.cpp
	${PST_SOURCE_DIR}/String.cpp
	${PST_SOURCE_DIR}/Method.cpp
	${PST_SOURCE_DIR}/Module.cpp
	${PST_SOURCE_DIR}/Tuple.cpp
	${PST_SOURCE_DIR}/Dictionary.cpp
)
source_group( src FILES ${SOURCES} )

# Library
add_library( ${PST_NAME} ${SOURCES} )
target_compile_features( ${PST_NAME} PRIVATE cxx_std_14 )
target_link_libraries( ${PST_NAME} PUBLIC ${PYTHON_LIBRARIES} )
set( PYSPOT_LIBRARIES ${PST_NAME} )
target_include_directories( ${PST_NAME} PUBLIC ${PST_INCLUDE_DIRS} )

enable_testing()
add_subdirectory( test )
