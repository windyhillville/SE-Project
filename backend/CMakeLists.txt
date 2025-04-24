cmake_minimum_required(VERSION 3.10)
# Comment this line below out if you are using macOS
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}external/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
project(SE-Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(src tests)

add_definitions(-DASIO_STANDALONE)

add_subdirectory(external/Crow)

add_executable(server src/main.cpp src/Planet.cpp src/DataProcessing.cpp)
#target_link_libraries(server
#       PUBLIC
#       Crow
#)
# Comment this line below out if you are using macOS and uncomment the one above
target_link_libraries(server PUBLIC Crow ws2_32 mswsock)

add_executable(run_tests tests/tests.cpp src/Planet.cpp src/DataProcessing.cpp)
# Comment this line below out if you are using macOS
target_link_libraries(run_tests PUBLIC Crow ws2_32 mswsock)
