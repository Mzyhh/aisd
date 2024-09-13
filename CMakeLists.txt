cmake_minimum_required(VERSION 3.29)
project(lab_sort C CXX)
set(CMAKE_C_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(playground sort.h main.c sort.c)


add_executable(sort_test sort.c sort_test.cxx)
target_link_libraries(sort_test gtest_main gmock_main)
add_test(NAME sort_test COMMAND sort_test)