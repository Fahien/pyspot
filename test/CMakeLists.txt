cmake_minimum_required( VERSION 3.12 )

project( pyspot-test LANGUAGES C CXX )

# Catch2
find_package( Catch2 REQUIRED )

set( TEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )

set( EXPORT_FILE ${TEST_SOURCE_DIR}/Export.cpp )

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
	${EXPORT_FILE}
	-- -xc++ -std=c++17 -DPY_MAJOR_VERSION=${PY_MAJOR_VERSION}
	-I${TEST_INCLUDE_DIR}
	-I${CMAKE_CURRENT_BINARY_DIR}/include
	-I${PST_INCLUDE_DIRS}
)

add_custom_target( ${PROJECT_NAME}-bindings
	COMMAND ${CMAKE_COMMAND} -E env CPLUS_INCLUDE_PATH=/usr/local/opt/llvm/include/c++/v1 $ENV{PYWRAP} ${COMMAND_ARGS}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating Bindings and Extension"
	VERBATIM
	COMMAND_EXPAND_LISTS
)

# Sources
set( TEST_SOURCES
	${TEST_SOURCE_DIR}/Main.cpp
	${TEST_SOURCE_DIR}/Interpreter.cpp
	${TEST_SOURCE_DIR}/Array.cpp
	${TEST_SOURCE_DIR}/Function.cpp
	${TEST_SOURCE_DIR}/Enum.cpp
	${TEST_SOURCE_DIR}/Struct.cpp
	${TEST_SOURCE_DIR}/Vec2.cpp
	${TEST_SOURCE_DIR}/Class.cpp
)
source_group( src FILES ${TEST_SOURCES} )

add_executable( ${PROJECT_NAME} ${TEST_SOURCES} ${GEN_SOURCES} )
add_dependencies( ${PROJECT_NAME} ${PROJECT_NAME}-bindings )
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
