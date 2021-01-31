cmake_minimum_required(VERSION 3.17)
project(double_to_float)
set(CMAKE_CXX_STANDARD 20)

FIND_PACKAGE(FLEX REQUIRED)

FLEX_TARGET(tokens data/patterns.flex ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
add_executable(double_to_float src/main.cpp ${FLEX_tokens_OUTPUTS} src/Scanner.cpp)
target_link_libraries(double_to_float -lfl)

enable_testing()
add_subdirectory("./test")
add_test(Name test/SimpleStringTest COMMAND SimpleStringTest)