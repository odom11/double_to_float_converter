//
// Created by ich on 1/31/21.
//

#include <iostream>
#include <stdexcept>
#include "Scanner.h"

extern "C"
int yylex(void);

extern "C"
char *yytext;

Scanner::~Scanner() {}

Scanner::Scanner() {
    assignment[0] = Token::END_OF_FILE;
    assignment[1] = Token::INTEGER;
    assignment[2] = Token::DOUBLE;
    assignment[3] = Token::FLOAT;
    assignment[4] = Token::MATH_FUNCTION;
    assignment[5] = Token::FLOAT_TYPE;
    assignment[6] = Token::END_OF_STATEMENT;
    assignment[7] = Token::BIN_OPERATOR;
}

std::pair<Token, std::string> Scanner::read() {
    int number = yylex();
    if (!assignment.contains(number)) {
        throw std::runtime_error("key " + std::to_string(number) + "not found");
    }
    auto it = assignment.find(number);
    return std::make_pair(it->second, std::string(yytext));
}

//std::ostream& operator<<(std::ostream& os, Token t) {
//    os << std::to_string(as_integer(t));
//};
