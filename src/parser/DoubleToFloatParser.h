//
// Created by ich on 2/1/21.
//

#ifndef DOUBLE_TO_FLOAT_DOUBLETOFLOATPARSER_H
#define DOUBLE_TO_FLOAT_DOUBLETOFLOATPARSER_H

#include <string>
#include <sstream>
#include "../scanner/Scanner.h"

class DoubleToFloatParser {
public:
    DoubleToFloatParser(Scanner& scanner);
    std::stringbuf parse();
private:
    Scanner& scanner;
};


#endif //DOUBLE_TO_FLOAT_DOUBLETOFLOATPARSER_H
