//
// Created by ich on 2/1/21.
//

#include "DoubleToFloatParser.h"

DoubleToFloatParser::DoubleToFloatParser(Scanner &scanner) : scanner(scanner) {}

std::stringbuf DoubleToFloatParser::parse() {
    std::stringbuf buf;
    auto add_to_buf = [&] (const char c) {buf.sputc(c);};
    for (ScannerOutput output = scanner.read(); std::get<TOKEN>(output) != Token::END_OF_FILE; output = scanner.read()) {
        Token t = std::get<TOKEN>(output);
        std::string s = std::get<TOKEN_STRING>(output);
        std::for_each(s.begin(), s.end(), add_to_buf);
        if (t == Token::MATH_FUNCTION || t == Token::DOUBLE) {
            buf.sputc('f');
        }
    }
    return buf;
}