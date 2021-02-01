//
// Created by ich on 1/31/21.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "SimpleStringTest"

#include <boost/test/unit_test.hpp>
#include <boost/assert.hpp>
#include "StringScanner.h"

extern "C"
char* yytext;

std::vector<ScannerOutput> getTestdata() {
    return std::vector<ScannerOutput>{
        std::make_pair(Token::INTEGER, "1234"),
        std::make_pair(Token::DOUBLE, "123.45"),
        std::make_pair(Token::DOUBLE, "123."),
        std::make_pair(Token::DOUBLE, ".3"),
        std::make_pair(Token::FLOAT, "1.f"),
        std::make_pair(Token::FLOAT, "1.F"),
        std::make_pair(Token::FLOAT, "1.2F"),
        std::make_pair(Token::MATH_FUNCTION, "sin"),
        std::make_pair(Token::MATH_FUNCTION, "cos"),
        std::make_pair(Token::FLOAT_TYPE, "float"),
        std::make_pair(Token::END_OF_STATEMENT, ";"),
        std::make_pair(Token::BIN_OPERATOR, "<<"),
        std::make_pair(Token::BIN_OPERATOR, "+"),
        std::make_pair(Token::BIN_OPERATOR, "*"),
        std::make_pair(Token::BIN_OPERATOR, "="),
        std::make_pair(Token::DUCK_BILL, "<foo>"),
        std::make_pair(Token::DUCK_BILL, "<<bar>"),
        std::make_pair(Token::STRING, "\"foo\""),
        std::make_pair(Token::IDENTIFIER, "sinfa"),
        std::make_pair(Token::MATH_FUNCTION_F, "sinf"),
        std::make_pair(Token::BLANK, " "),
        std::make_pair(Token::BLANK, "\n"),
        std::make_pair(Token::NAMESPACE, "::"),
        std::make_pair(Token::DEREF, "->"),
        std::make_pair(Token::ARGUMENT_LIST, ","),
        std::make_pair(Token::BRACKES, "["),
        std::make_pair(Token::BRACKES, "]"),
        std::make_pair(Token::BRACKES, "("),
        std::make_pair(Token::BRACKES, ")"),
        std::make_pair(Token::BRACKES, "{"),
        std::make_pair(Token::BRACKES, "}"),
        std::make_pair(Token::COMMENT, "//abc\n"),
        std::make_pair(Token::COMMENT, "/**/"),
        std::make_pair(Token::COMMENT, "/*abc*/"),
        std::make_pair(Token::COMMENT, "/*a\n bc*/"),
        std::make_pair(Token::COMMENT, "/*\n * NOTHING*/"),
    };
}

BOOST_AUTO_TEST_SUITE(SimpleStringTests)
BOOST_AUTO_TEST_CASE(foobar) {
    BOOST_CHECK_EQUAL(1,1);
}

BOOST_AUTO_TEST_CASE(testInteger) {
    std::string testString = "1234";
    StringScanner s(testString);

    auto result = s.read();
    BOOST_CHECK_EQUAL(Token::INTEGER, std::get<TOKEN>(result));
    BOOST_CHECK_EQUAL(testString, std::get<TOKEN_STRING>(result));
}

BOOST_AUTO_TEST_CASE(multi) {
    auto testdata = getTestdata();
    for (auto&  item : testdata) {
        StringScanner s(std::get<TOKEN_STRING>(item));
        auto result = s.read();
        BOOST_TEST_CONTEXT("scanning '" + std::get<TOKEN_STRING>(item) + "'") {
            std::cout << "\nscanned: '" << yytext << "', expected '" << std::get<TOKEN_STRING>(item) << "'" <<std::endl;
            BOOST_CHECK_EQUAL(std::get<TOKEN>(item), std::get<TOKEN>(result));
            BOOST_CHECK_EQUAL(std::get<TOKEN_STRING>(item), std::get<TOKEN_STRING>(result));
        }
    }
}

BOOST_AUTO_TEST_CASE(multilinecomment) {
    std::string commentline = "/****\n NOTHING*/";
    StringScanner s(commentline);
    auto result = s.read();
    std::cout << "expected to read: '" << commentline << "', got: '" << std::get<TOKEN_STRING>(result) << "'" << std::endl;
    BOOST_CHECK_EQUAL(std::get<TOKEN_STRING>(result), commentline);
}

BOOST_AUTO_TEST_CASE(zeroisanaturalnumber) {
    std::string something_went_wrong_here = "\tU = 0,";
    StringScanner s(something_went_wrong_here);
    for (auto t = s.read(); std::get<TOKEN>(t) != Token::END_OF_FILE; t = s.read()) {
        std::cout << std::get<TOKEN_STRING>(t) << std::endl;
    }
}
BOOST_AUTO_TEST_CASE(comparison) {
   std::string something_went_wrong_here = "((x)!=NULL) POV_FREE(x)";
   StringScanner s(something_went_wrong_here);
   for (auto t = s.read(); std::get<TOKEN>(t) != Token::END_OF_FILE; t = s.read()) {
       std::cout << std::get<TOKEN_STRING>(t) << std::endl;
   }
}
BOOST_AUTO_TEST_SUITE_END()