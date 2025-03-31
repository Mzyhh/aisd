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

file(GLOB_RECURSE BINARY_TREE_TEST_FILES tests/binary_tree*.cxx)
file(GLOB_RECURSE QUEUE_HM_TEST_FILES tests/queue_hm*.cxx)
file(GLOB_RECURSE LIST_PERSISTENT_TEST_FILES tests/list_persistent*.cxx)
file(GLOB_RECURSE SEGMENT_TREE_TEST_FILES tests/segment_tree*.cxx)
file(GLOB_RECURSE DISTINCT_NUMBERS_TEST_FILES tests/distinct_numbers*.cxx)
file(GLOB_RECURSE POINT_COUNT_TEST_FILES tests/point_count*.cxx)

message(STATUS "SRC_FILES: ${SRC_FILES}")
message(STATUS "SORT_TEST_FILES: ${SORT_TEST_FILES}")
message(STATUS "NTH_ELEMENT_TEST_FILES: ${NTH_ELEMENT_TEST_FILES}")
message(STATUS "BIGNUM_TEST_FILES: ${BIGNUM_TEST_FILES}")
message(STATUS "TREE23_TEST_FILES: ${TREE23_TEST_FILES}")

message(STATUS "BINARY_TREE_TEST_FILES: ${BINARY_TREE_TEST_FILES}")
message(STATUS "QUEUE_HM_TEST_FILES: ${QUEUE_HM_TEST_FILES}")
message(STATUS "LIST_PERSISTENT_TEST_FILES: ${LIST_PERSISTENT_TEST_FILES}")
message(STATUS "SEGMENT_TREE_TEST_FILES: ${SEGMENT_TREE_TEST_FILES}")
message(STATUS "DISTINCT_NUMBERS_TEST_FILES: ${DISTINCT_NUMBERS_TEST_FILES}")
message(STATUS "POINT_COUNT_TEST_FILES: ${POINT_COUNT_TEST_FILES}")

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

add_executable(binary_tree_test ${SRC_FILES} ${BINARY_TREE_TEST_FILES})
target_link_libraries(binary_tree_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(binary_tree_test PRIVATE headers)
add_test(NAME binary_tree_test COMMAND binary_tree_test)

add_executable(queue_hm_test ${SRC_FILES} ${QUEUE_HM_TEST_FILES})
target_link_libraries(queue_hm_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(queue_hm_test PRIVATE headers)
add_test(NAME queue_hm_test COMMAND queue_hm_test)

add_executable(list_persistent_test ${SRC_FILES} ${LIST_PERSISTENT_TEST_FILES})
target_link_libraries(list_persistent_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(list_persistent_test PRIVATE headers)
add_test(NAME list_persistent_test COMMAND list_persistent_test)

add_executable(segment_tree_test ${SRC_FILES} ${SEGMENT_TREE_TEST_FILES})
target_link_libraries(segment_tree_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(segment_tree_test PRIVATE headers)
add_test(NAME segment_tree_test COMMAND segment_tree_test)

add_executable(distinct_numbers_test ${SRC_FILES} ${DISTINCT_NUMBERS_TEST_FILES})
target_link_libraries(distinct_numbers_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(distinct_numbers_test PRIVATE headers)
add_test(NAME distinct_numbers_test COMMAND distinct_numbers_test)

add_executable(point_count_test ${SRC_FILES} ${POINT_COUNT_TEST_FILES})
target_link_libraries(point_count_test PRIVATE Catch2::Catch2WithMain)
target_include_directories(point_count_test PRIVATE headers)
add_test(NAME point_count_test COMMAND point_count_test)
