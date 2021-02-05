//
// Created by ich on 2/1/21.
//

#ifndef DOUBLE_TO_FLOAT_DOUBLETOFLOATPARSER_H
#define DOUBLE_TO_FLOAT_DOUBLETOFLOATPARSER_H

#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include "../scanner/Scanner.h"

class DoubleToFloatParser {
public:
    DoubleToFloatParser(Scanner& scanner);
    std::stringbuf parse() const;
private:
    const std::string processScannerOutput(const ScannerOutput& output) const;
    Scanner& scanner;
    std::unordered_map<Token, std::function<std::string(const std::string&)>> processors;
};


#endif //DOUBLE_TO_FLOAT_DOUBLETOFLOATPARSER_H
