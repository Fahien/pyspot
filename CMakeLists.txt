cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 11)

set(PST_TITLE PySpot)
set(PST_NAME  pyspot)
project(${PST_TITLE} C CXX)

# Version number
set(PST_VERSION_MAJOR 0)
set(PST_VERSION_MINOR 4)

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
set(PYTHON_VERSION "3" CACHE STRING "Python libraries version to use")
message(STATUS "Python Libraries Version: ${PYTHON_VERSION}")
add_definitions(-DPYTHON_VERSION=${PYTHON_VERSION})
find_package(PythonLibraries EXACT ${PYTHON_VERSION})

set(PST_INCLUDE_DIRS
	${PST_INCLUDE_DIR}
	${PST_GEN_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIR})

# Sources
set(SOURCES
	${PST_SOURCE_DIR}/Error.cpp
	${PST_SOURCE_DIR}/Interpreter.cpp
	${PST_SOURCE_DIR}/Object.cpp
	${PST_SOURCE_DIR}/Long.cpp
	${PST_SOURCE_DIR}/String.cpp
	${PST_SOURCE_DIR}/Method.cpp
	${PST_SOURCE_DIR}/Module.cpp
	${PST_SOURCE_DIR}/Tuple.cpp
	${PST_SOURCE_DIR}/Dictionary.cpp
)
source_group(src FILES ${SOURCES})

# Library
add_library(${PST_NAME} ${SOURCES})
target_link_libraries(${PST_NAME} PUBLIC ${PYTHON_LIBRARIES})
set(PYSPOT_LIBRARIES ${PST_NAME})
target_include_directories(${PST_NAME} PUBLIC ${PST_INCLUDE_DIRS})

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
	add_custom_command(
		TARGET PRE_BUILD
			${PYSPOT_LIBRARIES}
		COMMAND
			${CMAKE_COMMAND} -E copy
			${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_ANDROID_ARCH_ABI}/libpython2.7.so
			${CMAKE_BINARY_DIR}/libpython2.7.so)
endif()


# Generate the PytestExtension
include(ExtensionGenerator)
generate_extension(${CMAKE_CURRENT_SOURCE_DIR}/test/extension Pytest)

# Test Sources
set(TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test/src)
set(TEST_SOURCES
	${EXTENSION_SOURCES}
	${TEST_SOURCE_DIR}/tests.h
	${TEST_SOURCE_DIR}/tests.cpp
	${TEST_SOURCE_DIR}/main.cpp)
source_group("Tests" FILES ${TESTS})

# Test Executable
add_executable(pst-test ${TEST_SOURCES} ${TESTS})
target_include_directories(pst-test PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/test/include
	${CMAKE_CURRENT_BINARY_DIR}/include
	${PST_INCLUDE_DIRS})
target_link_libraries(pst-test ${PYSPOT_LIBRARIES})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/script DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test)

# Test
add_test(pst-test ${EXECUTABLE_OUTPUT_PATH}/pst-test)

include(CTest)
