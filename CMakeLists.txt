cmake_minimum_required(VERSION 3.29)
project(lab_sort C CXX)
set(CMAKE_C_STANDARD 17)
link_libraries(m)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.0
)

FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE SRC_FILES src/*.c)
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/src/main.c")

file(GLOB_RECURSE SORT_TEST_FILES tests/sort*.cxx)
file(GLOB_RECURSE NTH_ELEMENT_TEST_FILES tests/nth_element*.cxx)

message(STATUS "SRC_FILES: ${SRC_FILES}")
message(STATUS "SORT_TEST_FILES: ${SORT_TEST_FILES}")
message(STATUS "NTH_ELEMENT_TEST_FILES: ${NTH_ELEMENT_TEST_FILES}")

add_executable(playground src/main.c ${SRC_FILES}
        headers/sort.h
        headers/nth_element.h)
target_include_directories(playground PRIVATE headers)

add_executable(sort_test ${SRC_FILES} ${SORT_TEST_FILES})
target_link_libraries(sort_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(sort_test PRIVATE headers)
add_test(NAME sort_test COMMAND sort_test)

add_executable(nth_element_test ${SRC_FILES} ${NTH_ELEMENT_TEST_FILES})
target_link_libraries(nth_element_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(nth_element_test PRIVATE headers)
add_test(NAME nth_element_test COMMAND nth_element_test)
