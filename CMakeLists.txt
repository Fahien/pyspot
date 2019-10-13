cmake_minimum_required( VERSION 3.12 )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_C_STANDARD 11 )

project( pyspot
	VERSION 0.9
	LANGUAGES C CXX
)

# Directories
set( PST_SCRIPT_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/script )
set( PST_SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( PST_INCLUDE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( PST_GEN_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include )

# Configure a header file to pass some of the CMake settings to the source code
configure_file( ${PST_SOURCE_DIR}/Config.h.in ${PST_GEN_INCLUDE_DIR}/Config.h )

# CMake modules
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
find_package( Python3 COMPONENTS Development )

set( PST_INCLUDE_DIRS
	${PST_INCLUDE_DIR}
	${PST_GEN_INCLUDE_DIR}
	${Python3_INCLUDE_DIRS}
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
add_library( ${PROJECT_NAME} ${SOURCES} )
target_compile_features( ${PROJECT_NAME} PRIVATE cxx_std_17 )
target_link_libraries( ${PROJECT_NAME} PUBLIC ${Python3_LIBRARIES} )
set( PYSPOT_LIBRARIES ${PROJECT_NAME} )
target_include_directories( ${PROJECT_NAME} PUBLIC ${PST_INCLUDE_DIRS} )

add_subdirectory( test )
