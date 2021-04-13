cmake_minimum_required(VERSION 3.17)
project(timer)
set(CMAKE_CXX_STANDARD 20)
find_package(Qt5Widgets REQUIRED)

add_executable(timer main.cpp Data.cpp Data.h Window.cpp Window.h )
target_link_libraries(timer Qt5::Widgets)
add_subdirectory(Google_tests)