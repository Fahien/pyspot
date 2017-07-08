cmake_minimum_required(VERSION 3.0.2)
project(PySpoT)

# Version number
set(PST_VERSION_MAJOR 0)
set(PST_VERSION_MINOR 1)
set(PST_TITLE "PySpoT")

# Module path
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/cmake")
message("Searching modules in ${CMAKE_MODULE_PATH}")

# Source dir
set(PST_SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src")
set(PST_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

# Configure a header file to pass some of the CMake settings to the source code
configure_file("${PST_SOURCE_DIR}/Config.h.in"
               "${PST_INCLUDE_DIR}/Config.h")

include_directories("${PST_SOURCE_DIR}"
                    "${PST_INCLUDE_DIR}")

find_package(PythonInterp 3)
find_package(PythonLibs 3)

set(SOURCES
    ${PST_SOURCE_DIR}/PySpotException.h
    ${PST_SOURCE_DIR}/PySpot.h
    ${PST_SOURCE_DIR}/PySpot.cpp
    ${PST_SOURCE_DIR}/PySpotObject.h
    ${PST_SOURCE_DIR}/PySpotObject.cpp
    ${PST_SOURCE_DIR}/PySpotString.h
    ${PST_SOURCE_DIR}/PySpotString.cpp
    ${PST_SOURCE_DIR}/PySpotFunction.h
    ${PST_SOURCE_DIR}/PySpotFunction.cpp
    ${PST_SOURCE_DIR}/PySpotModule.h
    ${PST_SOURCE_DIR}/PySpotModule.cpp
)
source_group("Sources" FILES ${SOURCES})

# Tests
include(test)
