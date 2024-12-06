cmake_minimum_required(VERSION 3.29)
project(lab_sort C CXX)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)
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
file(GLOB_RECURSE BIGNUM_TEST_FILES tests/bignum*.cxx)
file(GLOB_RECURSE TREE23_TEST_FILES tests/tree_23*.cxx)

message(STATUS "SRC_FILES: ${SRC_FILES}")
message(STATUS "SORT_TEST_FILES: ${SORT_TEST_FILES}")
message(STATUS "NTH_ELEMENT_TEST_FILES: ${NTH_ELEMENT_TEST_FILES}")
message(STATUS "BIGNUM_TEST_FILES: ${BIGNUM_TEST_FILES}")
message(STATUS "TREE23_TEST_FILES: ${TREE23_TEST_FILES}")

add_executable(playground src/main.c ${SRC_FILES})
target_include_directories(playground PRIVATE headers)

add_executable(sort_test ${SRC_FILES} ${SORT_TEST_FILES})
target_link_libraries(sort_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(sort_test PRIVATE headers)
add_test(NAME sort_test COMMAND sort_test)

add_executable(nth_element_test ${SRC_FILES} ${NTH_ELEMENT_TEST_FILES})
target_link_libraries(nth_element_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(nth_element_test PRIVATE headers)
add_test(NAME nth_element_test COMMAND nth_element_test)

add_executable(bignum_test ${SRC_FILES} ${BIGNUM_TEST_FILES})
target_link_libraries(bignum_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(bignum_test PRIVATE headers)
add_test(NAME bignum_test COMMAND bignum_test)

add_executable(tree23_test ${SRC_FILES} ${TREE23_TEST_FILES})
target_link_libraries(tree23_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(tree23_test PRIVATE headers)
add_test(NAME tree23_test COMMAND tree23_test)
