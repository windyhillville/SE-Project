cmake_minimum_required(VERSION 3.10)
project(SE-Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(src tests)

add_executable(main_app src/main.cpp src/Planet.cpp)

add_executable(run_tests tests/tests.cpp src/Planet.cpp)
