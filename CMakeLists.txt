cmake_minimum_required(VERSION 3.10)
project(SE-Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(src tests)

add_definitions(-DASIO_STANDALONE)

add_subdirectory(external/Crow)

add_executable(Elysium src/main.cpp src/Planet.cpp src/DataProcessing.cpp)

target_link_libraries(Elysium
        PUBLIC
        Crow
)

add_executable(run_tests tests/tests.cpp src/Planet.cpp src/DataProcessing.cpp)
