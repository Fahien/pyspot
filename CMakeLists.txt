cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 11)

set(PST_TITLE PySpot)
project(${PST_TITLE} C CXX)

# Version number
set(PST_VERSION_MAJOR 0)
set(PST_VERSION_MINOR 3)

# Source dir
set(PST_SOURCE_DIR  ${PROJECT_SOURCE_DIR}/src)
set(PST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PST_GEN_INCLUDE_DIR ${PROJECT_BINARY_DIR}/include)

# Configure a header file to pass some of the CMake settings to the source code
configure_file(${PST_SOURCE_DIR}/Config.h.in
			   ${PST_GEN_INCLUDE_DIR}/Config.h)

# CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(PythonInterp 3)
find_package(PythonLibraries)

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
source_group(Sources FILES ${SOURCES})

# Library
add_library(pyspot ${SOURCES})
target_link_libraries(pyspot PUBLIC ${PYTHON_LIBRARIES})
set(PYSPOT_LIBRARIES pyspot)
target_include_directories(pyspot PUBLIC ${PST_INCLUDE_DIRS})

if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
	add_custom_command(
		TARGET PRE_BUILD
			${PYSPOT_LIBRARIES}
		COMMAND
			${CMAKE_COMMAND} -E copy
			${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_ANDROID_ARCH_ABI}/libpython2.7.so
			${CMAKE_BINARY_DIR}/libpython2.7.so)
endif()


# Generate the PytestExtension header
set(EXTENSION_NAME "Pytest")
set(EXTENSION_JSON "${PROJECT_SOURCE_DIR}/test/extension/pytest/${EXTENSION_NAME}.json")
set(EXTENSION_HEADER ${PROJECT_BINARY_DIR}/test/include/pytest/extension/${EXTENSION_NAME}.h)
set(EXTENSION_SOURCE ${PROJECT_BINARY_DIR}/test/src/pytest/extension/${EXTENSION_NAME}.cpp)
add_custom_command(
	OUTPUT ${EXTENSION_HEADER} ${EXTENSION_SOURCE}
	COMMAND ${PYTHON_EXECUTABLE} generate-extension.py ${EXTENSION_JSON} -h ${EXTENSION_HEADER}
	COMMAND ${PYTHON_EXECUTABLE} generate-extension.py ${EXTENSION_JSON} ${EXTENSION_SOURCE}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/script
	COMMENT "Generating ${EXTENSION}"
	VERBATIM)

# Get all the folders under test/extension/pytest
set(PYTEST_PATH ${PROJECT_SOURCE_DIR}/test/extension/pytest)
file(GLOB NAMESPACES LIST_DIRECTORY true ${PYTEST_PATH}/*)
foreach(NAMESPACE ${NAMESPACES})
	if(IS_DIRECTORY ${NAMESPACE})
		# Get all the jsons and generate headers
		file(GLOB COMPONENTS ${NAMESPACE}/*json)
		foreach(COMPONENT ${COMPONENTS})
			get_filename_component(NAMESPACE_NAME ${NAMESPACE} NAME_WE)
			get_filename_component(NAME ${COMPONENT} NAME_WE)
			list(APPEND COMPONENT_NAMES ${NAME})
			set(COMPONENT_HEADER ${PROJECT_BINARY_DIR}/test/include/pytest/${NAMESPACE_NAME}/${NAME}.h)
			list(APPEND COMPONENT_HEADERS ${COMPONENT_HEADER})
			add_custom_command(
				OUTPUT ${COMPONENT_HEADER}
				COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/script/generate-component.py ${EXTENSION_NAME} ${COMPONENT} ${COMPONENT_HEADER}
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/script
				COMMENT "Generating ${COMPONENT_HEADER}"
				VERBATIM)
		endforeach()
	endif()
endforeach()


# Test Sources
set(TEST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/test/src)
set(TEST_SOURCES
	${COMPONENT_HEADERS}
	${ENUM_HEADERS}
	${EXTENSION_HEADER}
	${EXTENSION_SOURCE}
	${TEST_SOURCE_DIR}/tests.h
	${TEST_SOURCE_DIR}/tests.cpp
	${TEST_SOURCE_DIR}/main.cpp)
source_group("Tests" FILES ${TESTS})

# Test Executable
add_executable(pyspot-test ${TEST_SOURCES} ${TESTS})
target_include_directories(pyspot-test PRIVATE
	${PROJECT_SOURCE_DIR}/test/include
	${PROJECT_BINARY_DIR}/test/include
	${PST_INCLUDE_DIRS})
target_link_libraries(pyspot-test ${PYSPOT_LIBRARIES})
file(COPY ${PROJECT_SOURCE_DIR}/test/script DESTINATION ${PROJECT_BINARY_DIR}/test)

# Test
add_test(pyspot-test ${EXECUTABLE_OUTPUT_PATH}/pyspot-test)

include(CTest)
