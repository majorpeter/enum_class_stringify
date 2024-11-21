cmake_minimum_required(VERSION 3.11)
project(basic_test)

set(GTEST_VERSION 1.15.2 CACHE STRING "Google test version")

include(FetchContent)
FetchContent_Declare(googletest
GIT_REPOSITORY https://github.com/google/googletest.git
GIT_TAG v${GTEST_VERSION})

FetchContent_MakeAvailable(googletest)

add_executable(runUnitTests test/tests.cpp test/testclass.cpp)
set_property(TARGET runUnitTests PROPERTY CXX_STANDARD 20)

include_directories(${googletest_SOURCE_DIR}/include)
target_link_libraries(runUnitTests gtest gtest_main)

enable_testing()
add_test(runUnitTests runUnitTests)
