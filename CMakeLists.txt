cmake_minimum_required(VERSION 3.6)
project(PySpoT)

# Version number
set(PST_VERSION_MAJOR 0)
set(PST_VERSION_MINOR 1)
set(PST_TITLE PySpoT)

# Source dir
set(PST_SOURCE_DIR  ${PROJECT_SOURCE_DIR}/src)
set(PST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# Configure a header file to pass some of the CMake settings to the source code
configure_file(${PST_SOURCE_DIR}/PySpotConfig.h.in
               ${PST_INCLUDE_DIR}/PySpotConfig.h)

find_package(PythonInterp 3)
find_package(PythonLibs 3)

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
)
source_group(Sources FILES ${SOURCES})

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# Library
add_library(pyspot ${SOURCES})
set_target_properties(pyspot PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(pyspot ${PYTHON_LIBRARIES})
