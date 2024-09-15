cmake_minimum_required(VERSION 3.29)
project(lab_sort C CXX)
set(CMAKE_C_STANDARD 17)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.7.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(playground main.c sort.h sort.c)

add_executable(sort_test sort.c sort_test.cxx)
target_link_libraries(sort_test PRIVATE Catch2::Catch2WithMain)
add_test(NAME sort_test COMMAND sort_test)
