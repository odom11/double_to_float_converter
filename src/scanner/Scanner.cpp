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

extern int column_number, line_number;

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
    assignment[8] = Token::DUCK_BILL;
    assignment[9] = Token::STRING;
    assignment[10] = Token::IDENTIFIER;
    assignment[41] = Token::MATH_FUNCTION_F;
    assignment[11] = Token::BLANK;
    assignment[12] = Token::NAMESPACE;
    assignment[13] = Token::DEREF;
    assignment[14] = Token::ARGUMENT_LIST;
    assignment[15] = Token::BRACKES;
    assignment[16] = Token::PREPROCESSOR;
    assignment[17] = Token::COMMENT;

}

std::pair<Token, std::string> Scanner::read() {
    int number = yylex();
    if (!assignment.contains(number)) {
        throw std::runtime_error("key " + std::to_string(number) + " not found");
    }
    auto it = assignment.find(number);
    return std::make_pair(it->second, std::string(yytext));
}

void Scanner::resetLineCounter() {
    column_number = 1;
    line_number = 1;
}

//std::ostream& operator<<(std::ostream& os, Token t) {
//    os << std::to_string(as_integer(t));
//};
