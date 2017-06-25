cmake_minimum_required(VERSION 3.0.2)
project(PySpoT)

# Version number
set(PST_VERSION_MAJOR 0)
set(PST_VERSION_MINOR 1)
set(PST_TITLE "PySpoT")

# Configure a header file to pass some of the CMake settings to the source code
configure_file("${PROJECT_SOURCE_DIR}/src/Config.h.in"
               "${PROJECT_SOURCE_DIR}/include/Config.h")

include_directories("${PROJECT_SOURCE_DIR}/src"
                    "${PROJECT_SOURCE_DIR}/include")

find_package(PythonInterp 3)
find_package(PythonLibs 3)

set(SOURCES
    src/PySpotException.h
    src/PySpot.h
    src/PySpot.cpp
    src/PySpotObject.h
    src/PySpotObject.cpp
    src/PySpotString.h
    src/PySpotString.cpp
    src/PySpotFunction.h
    src/PySpotFunction.cpp
    src/PySpotModule.h
    src/PySpotModule.cpp
)
source_group("Sources" FILES ${SOURCES})

set(TESTS
    test/tests.h
    test/tests.cpp
    test/main.cpp)
source_group("Tests" FILES ${TESTS})

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_executable(pyspot-test ${SOURCES} ${TESTS})

target_include_directories(pyspot-test PUBLIC
                           "${PYTHON_INCLUDE_DIR}")

set_target_properties(pyspot-test PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(pyspot-test ${PYTHON_LIBRARIES})

add_test(pyspot-test
         ${EXECUTABLE_OUTPUT_PATH}/pyspot-test)

include(CTest)
