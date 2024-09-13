cmake_minimum_required(VERSION 3.29)
project(test1 C CXX)

set(CMAKE_C_STANDARD 17)

add_executable(test1 main.c)
add_library(sample sample1.cxx)





include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(example sample1.cxx sample1_unittest.cxx)
target_link_libraries(example gtest_main)
add_test(NAME example_test COMMAND example)