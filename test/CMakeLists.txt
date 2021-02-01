cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(FLEX REQUIRED)

include_directories(BEFORE ${BOOST_INCLUDE_DIRS} ../include)

FLEX_TARGET(tokens ../data/patterns.flex ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)

SET(SCANNERFILES ../src/scanner/Scanner.cpp ../src/scanner/StringScanner.cpp ../src/scanner/MultilineCommentResistantStringScanner.cpp)

add_executable(SimpleStringTest SimpleStringTest.cpp ${SCANNERFILES} ${FLEX_tokens_OUTPUTS})
target_link_libraries(SimpleStringTest ${Boost_LIBRARIES} ${FLEX_LIBRARIES})

add_executable(SourceStringTest SourceStringTest.cpp ${SCANNERFILES} ${FLEX_tokens_OUTPUTS})
target_link_libraries(SourceStringTest ${Boost_LIBRARIES} ${FLEX_LIBRARIES})