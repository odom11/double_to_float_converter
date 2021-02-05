cmake_minimum_required(VERSION 3.17)
project(double_to_float)
set(CMAKE_CXX_STANDARD 20)

FIND_PACKAGE(FLEX REQUIRED)

FLEX_TARGET(tokens data/patterns.flex ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)

include_directories(BEFORE include)

file(GLOB_RECURSE sourcefiles src/*.cpp)
add_executable(double_to_float ${sourcefiles} ${FLEX_tokens_OUTPUTS})
target_link_libraries(double_to_float ${FLEX_LIBRARIES})

enable_testing()
add_subdirectory("./test")