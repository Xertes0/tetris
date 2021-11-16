cmake_minimum_required(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

project(tetris VERSION 0.1 LANGUAGES CXX)

set(CMAKE_BINARY_DIR bin)
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH bin)

set(CMAKE_CXX_STANDARD 20 REQUIRED)

find_package(SFML COMPONENTS graphics window REQUIRED)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE INC include/*.hpp)

add_executable(tetris)
target_sources(tetris PRIVATE ${SRC} ${INC})
target_include_directories(tetris PRIVATE include)
target_link_libraries(tetris PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} sfml-graphics sfml-window fmt)
