cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 11)

project(PySpoT)

# Version number
set(PST_VERSION_MAJOR 0)
set(PST_VERSION_MINOR 2)
set(PST_TITLE PySpoT)

# Source dir
set(PST_SOURCE_DIR  ${PROJECT_SOURCE_DIR}/source)
set(PST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# Configure a header file to pass some of the CMake settings to the source code
configure_file(${PST_SOURCE_DIR}/PySpotConfig.h.in
               ${PST_INCLUDE_DIR}/PySpotConfig.h)

find_package(PythonInterp 3)
find_package(PythonLibs   3)

include_directories(${PST_SOURCE_DIR}
                    ${PST_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_DIR})

# Sources
set(SOURCES
    ${PST_SOURCE_DIR}/PySpot.cpp
    ${PST_SOURCE_DIR}/PySpotObject.cpp
    ${PST_SOURCE_DIR}/PySpotString.cpp
    ${PST_SOURCE_DIR}/PySpotFunction.cpp
    ${PST_SOURCE_DIR}/PySpotModule.cpp
    ${PST_SOURCE_DIR}/PySpotTuple.cpp
)
source_group(Sources FILES ${SOURCES})

# Library
add_library(pyspot ${SOURCES})
set_target_properties(pyspot PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(pyspot ${PYTHON_LIBRARIES})


# Get all the json in test/component and generate headers
file(GLOB COMPONENTS test/component/*json)
foreach(COMPONENT ${COMPONENTS})
    get_filename_component(NAME ${COMPONENT} NAME_WE)
    list(APPEND COMPONENT_NAMES ${NAME})
    set(COMPONENT_HEADER ${PROJECT_BINARY_DIR}/test/component/${NAME}.h)
    list(APPEND COMPONENT_HEADERS ${COMPONENT_HEADER})
    add_custom_command(
        OUTPUT ${COMPONENT_HEADER}
        COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/script/generate-component.py ${COMPONENT} > ${COMPONENT_HEADER}
        COMMENT "Generating ${COMPONENT_HEADER}"
        VERBATIM)
endforeach()

# Generate the PySpotExtension header
set(EXTENSION_HEADER ${PROJECT_BINARY_DIR}/test/extension/PySpotExtension.h)
set(EXTENSION_SOURCE ${PROJECT_BINARY_DIR}/test/extension/PySpotExtension.cpp)
add_custom_command(
    OUTPUT ${EXTENSION_HEADER} ${EXTENSION_SOURCE}
    COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/script/generate-extension.py -h > ${EXTENSION_HEADER}
    COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/script/generate-extension.py ${COMPONENT_NAMES} > ${EXTENSION_SOURCE}
    COMMENT "Generating ${EXTENSION}"
    VERBATIM)

# Test Sources
set(TEST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/test/source)
set(TEST_SOURCES
    ${COMPONENT_HEADERS}
    ${EXTENSION_HEADER}
    ${EXTENSION_SOURCE}
    ${TEST_SOURCE_DIR}/tests.h
    ${TEST_SOURCE_DIR}/tests.cpp
    ${TEST_SOURCE_DIR}/main.cpp)
source_group("Tests" FILES ${TESTS})

# Test Executable
add_executable(pyspot-test ${TEST_SOURCES} ${TESTS})
set_target_properties(pyspot-test PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(pyspot-test PUBLIC
    ${PROJECT_BINARY_DIR}/test/component
    ${PROJECT_BINARY_DIR}/test/extension)
target_link_libraries(pyspot-test pyspot)
file(COPY ${PROJECT_SOURCE_DIR}/test/script DESTINATION ${PROJECT_BINARY_DIR}/test)

# Test
add_test(pyspot-test ${EXECUTABLE_OUTPUT_PATH}/pyspot-test)

include(CTest)