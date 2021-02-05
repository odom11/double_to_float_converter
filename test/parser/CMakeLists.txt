cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(FLEX REQUIRED)

include_directories(BEFORE ${BOOST_INCLUDE_DIRS})

FLEX_TARGET(tokens ../../data/patterns.flex ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
SET(SCANNERFILES ../../src/scanner/Scanner.cpp ../../src/scanner/StringScanner.cpp ../../src/scanner/MultilineCommentResistantStringScanner.cpp)
SET(PARSERFILES ../../src/parser/DoubleToFloatParser.cpp)

add_executable(ParserTest ParserTest.cpp ${FLEX_tokens_OUTPUTS} ${SCANNERFILES} ${PARSERFILES})
target_link_libraries(ParserTest ${Boost_LIBRARIES} ${FLEX_LIBRARIES})
add_test(NAME test/parser/ParserTest COMMAND ParserTest)
