cmake_minimum_required( VERSION 3.6 )

project( PySpotTest LANGUAGES C CXX )

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/module/gtest )

# Headers
set( TEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( TEST_HEADER ${TEST_INCLUDE_DIR}/test/Test.h )

# Pyspot extension files
set( GEN_SOURCES
	${CMAKE_CURRENT_BINARY_DIR}/src/pyspot/Bindings.cpp
	${CMAKE_CURRENT_BINARY_DIR}/src/pyspot/Extension.cpp
)

# Set PY_MAJOR_VERSION
if( ${PYTHONLIBS_VERSION_STRING} MATCHES "3" )
	set( PY_MAJOR_VERSION 3 )
elseif( ${PYTHONLIBS_VERSION_STRING} MATCHES "2" )
	set( PY_MAJOR_VERSION 2 )
else()
	message( FATAL "PythonLibs v${PYTHONLIBS_VERSION_STRING} unsupported" )
endif()

# Join function
function( join VALUES GLUE OUTPUT )
	string( REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}" )
	string( REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}" ) # fixes escaping
	set( ${OUTPUT} "${_TMP_STR}" PARENT_SCOPE )
endfunction()

# Generation command
set( GEN_INCLUDE_DIRS
	${TEST_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}/include
	${PST_INCLUDE_DIRS}
)
join( "${GEN_INCLUDE_DIRS}" "\" -I\"" I_GEN_INCLUDE_DIRS )
set( I_GEN_INCLUDE_DIRS "\"${I_GEN_INCLUDE_DIRS}\"" )
add_custom_command( OUTPUT ${GEN_SOURCES} always
	COMMAND pywrap
	ARGS ${TEST_HEADER} -o pyspot -- -I${I_GEN_INCLUDE_DIRS} -xc++ -std=c++11 -DPY_MAJOR_VERSION=${PY_MAJOR_VERSION}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating Bindings and Extension"
)

# Sources
set( TEST_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( TEST_SOURCES
	${GEN_SOURCES}
	${TEST_SOURCE_DIR}/Main.cpp
	${TEST_SOURCE_DIR}/Interpreter.cpp
	${TEST_SOURCE_DIR}/Enum.cpp
)

source_group( src FILES ${TEST_SOURCES} )
add_executable( pyspot-test ${TEST_SOURCES} )
target_compile_features( pyspot-test PRIVATE cxx_std_11 )
target_include_directories( pyspot-test PRIVATE ${GEN_INCLUDE_DIRS})
target_link_libraries( pyspot-test pyspot gtest )

include(CTest)
add_test(NAME pyspot-test
	COMMAND $<TARGET_FILE:pyspot-test>
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
