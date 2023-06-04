cmake_minimum_required(VERSION 3.22)
project(simplesgraphes)

set(CMAKE_CXX_STANDARD 14)

add_executable(simplesgraphes main.cpp)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tests)
