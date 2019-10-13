cmake_minimum_required( VERSION 3.12 )

project( pyspot-test LANGUAGES C CXX )

# Catch2
find_package( Catch2 REQUIRED )

# Headers
set( TEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( EXPORT_HEADER ${TEST_INCLUDE_DIR}/test/Export.hpp )

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
if( ${Python3_VERSION_MAJOR} EQUAL 3 )
	set( PY_MAJOR_VERSION 3 )
else()
	message( FATAL_ERROR "Python v${Python3_VERSION} not supported" )
endif()

# Generation command
set( COMMAND_ARGS
	${EXPORT_HEADER}
	-- -xc++ -std=c++17 -DPY_MAJOR_VERSION=${PY_MAJOR_VERSION}
	-I${TEST_INCLUDE_DIR}
	-I${CMAKE_CURRENT_BINARY_DIR}/include
	-I${PST_INCLUDE_DIRS}
)

add_custom_command( OUTPUT ${GEN_SOURCES} always
	COMMAND $ENV{PYWRAP}
	ARGS ${COMMAND_ARGS}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating Bindings and Extension"
	COMMAND_EXPAND_LISTS
	VERBATIM
)

# Sources
set( TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( TEST_SOURCES
	${TEST_INCLUDE_DIR}/test/Test.h
	${TEST_INCLUDE_DIR}/test/Export.hpp
	${TEST_INCLUDE_DIR}/test/Product.h
	${TEST_INCLUDE_DIR}/test/Color.h
	${TEST_SOURCE_DIR}/Main.cpp
	${TEST_SOURCE_DIR}/Interpreter.cpp
	${TEST_SOURCE_DIR}/Function.cpp
	${TEST_SOURCE_DIR}/Enum.cpp
	${TEST_SOURCE_DIR}/Struct.cpp
	${TEST_SOURCE_DIR}/Vec2.cpp
	${TEST_SOURCE_DIR}/Class.cpp
)
source_group( src FILES ${TEST_SOURCES} )

add_executable( ${PROJECT_NAME} ${TEST_SOURCES} ${GEN_SOURCES} )
target_compile_features( ${PROJECT_NAME} PRIVATE cxx_std_17 )
target_include_directories( ${PROJECT_NAME}
	PRIVATE
		${TEST_INCLUDE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/include
		${PST_INCLUDE_DIRS}
)
target_link_libraries( ${PROJECT_NAME} pyspot Catch2::Catch2 )

enable_testing()
add_test( NAME ${PROJECT_NAME}
	COMMAND $<TARGET_FILE:${PROJECT_NAME}>
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
