//
// Created by ich on 2/1/21.
//
#include <iostream>
#include "DoubleToFloatParser.h"

extern int line_number;

DoubleToFloatParser::DoubleToFloatParser(Scanner &scanner) : scanner(scanner) {
    processors[Token::DOUBLE_TYPE] = [] (const std::string&) {return "float";};
    processors[Token::MATH_FUNCTION] = [] (const std::string& s) {return s + "f";};
    processors[Token::DOUBLE] = [] (const std::string& s) {return s + "f";};
    // linecounting is errorprone.
    //processors[Token::NEWLINE] = [] (const std::string& s) {return s + std::to_string(line_number) + "\t";};
}
extern int column_number, line_number;

std::stringbuf DoubleToFloatParser::parse() const {
    std::stringbuf buf;
    auto add_to_buf = [&] (const char c) {buf.sputc(c);};
    for (ScannerOutput output = scanner.read();
         std::get<TOKEN>(output) != Token::END_OF_FILE; output = scanner.read()) {
        const std::string processed = processScannerOutput(output);
        std::for_each(processed.begin(), processed.end(), add_to_buf);
    }
    return buf;
}

const std::string DoubleToFloatParser::processScannerOutput(const ScannerOutput &output) const {
    Token t = std::get<TOKEN>(output);
    std::string s = std::get<TOKEN_STRING>(output);
    if (processors.contains(t)) {
        auto processor = processors.find(t)->second;
        return processor(s);
    } else {
        return s;
    }
}