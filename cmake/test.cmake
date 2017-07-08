set(TESTS
    test/module/pytestmodule.h
    test/module/pytestmodule.cpp
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

file(COPY ${PROJECT_SOURCE_DIR}/script DESTINATION ${PROJECT_BINARY_DIR})

include(CTest)
