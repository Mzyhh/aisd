cmake_minimum_required(VERSION 3.29)
project(test1 C CXX)

set(CMAKE_C_STANDARD 17)

add_executable(playground main.c sorts.h sorts.c)
add_library(sorts sorts.c sorts.h)


include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(sort_tests sorts.c sort_tests.cxx)
target_link_libraries(sort_tests gtest_main gmock_main)
#add_test(NAME sort_tests3 COMMAND sort_tests2)