cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)

project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cc)

add_executable(Google_Tests_run DataTest.cpp ../Data.cpp ../Data.h ${SRC_FILES})
target_link_libraries(Google_Tests_run gtest gtest_main)