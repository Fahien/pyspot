cmake_minimum_required( VERSION 3.6 )

project( PySpotTest LANGUAGES C CXX )

# Google test
if( MSVC )
	set( gtest_force_shared_crt ON )
endif()
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/module/gtest )

# Headers
set( TEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( EXPORT_HEADER ${TEST_INCLUDE_DIR}/test/Export.h )

# Pyspot extension files
set( GEN_SOURCES
	${CMAKE_CURRENT_BINARY_DIR}/include/pyspot/Bindings.h
	${CMAKE_CURRENT_BINARY_DIR}/include/pyspot/Extension.h
	${CMAKE_CURRENT_BINARY_DIR}/src/pyspot/Bindings.cpp
	${CMAKE_CURRENT_BINARY_DIR}/src/pyspot/Extension.cpp
)
set_source_files_properties( ${GEN_SOURCES} PROPERTIES GENERATED TRUE )
source_group( gen FILES ${GEN_SOURCES} )

# Set PY_MAJOR_VERSION
if( ${PYTHONLIBS_VERSION_STRING} MATCHES "3" )
	set( PY_MAJOR_VERSION 3 )
else()
	message( FATAL_ERROR "PythonLibs v${PYTHONLIBS_VERSION_STRING} unsupported" )
endif()

# Join function
function( join VALUES GLUE OUTPUT )
	string( REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}" )
	string( REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}" ) # fixes escaping
	set( ${OUTPUT} "${_TMP_STR}" PARENT_SCOPE )
endfunction()

# Generation command
set( COMMAND_ARGS
	${EXPORT_HEADER} -o pyspot
	-- -xc++ -std=c++14 -DPY_MAJOR_VERSION=${PY_MAJOR_VERSION}
	-I${TEST_INCLUDE_DIR}
	-I${CMAKE_CURRENT_BINARY_DIR}/include
	-I${PST_INCLUDE_DIRS}
)

foreach( INCLUDE_DIR ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES} )
	list( APPEND COMMAND_ARGS -I${INCLUDE_DIR} )
endforeach()

set( CMAKE_VERBOSE_MAKEFILE on )
add_custom_command( OUTPUT ${GEN_SOURCES}
	COMMAND pywrap
	ARGS ${COMMAND_ARGS}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating Bindings and Extension"
	COMMAND_EXPAND_LISTS
	VERBATIM
)

# Sources
set( TEST_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( TEST_SOURCES
	${TEST_INCLUDE_DIR}/test/Test.h
	${TEST_INCLUDE_DIR}/test/Export.h
	${TEST_INCLUDE_DIR}/test/Product.h
	${TEST_INCLUDE_DIR}/test/Color.h
	${TEST_SOURCE_DIR}/Main.cpp
	${TEST_SOURCE_DIR}/Interpreter.cpp
	${TEST_SOURCE_DIR}/Function.cpp
	${TEST_SOURCE_DIR}/Enum.cpp
	${TEST_SOURCE_DIR}/Struct.cpp
	#${TEST_SOURCE_DIR}/Product.cpp
)
source_group( src FILES ${TEST_SOURCES} )

add_executable( pyspot-test ${TEST_SOURCES} ${GEN_SOURCES} )
target_compile_features( pyspot-test PRIVATE cxx_std_11 )
target_include_directories( pyspot-test
	PRIVATE
	${TEST_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}/include
	${PST_INCLUDE_DIRS}
)
target_link_libraries( pyspot-test pyspot gtest )

add_test( NAME pyspot-test
	COMMAND $<TARGET_FILE:pyspot-test>
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
