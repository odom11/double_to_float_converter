//
// Created by ich on 1/31/21.
//

#ifndef DOUBLE_TO_FLOAT_STRINGSCANNER_H
#define DOUBLE_TO_FLOAT_STRINGSCANNER_H

#include "../src/scanner/Scanner.h"

class StringScanner : public Scanner {
public:
    explicit StringScanner(const std::string& str);
private:
    std::string str;
};


#endif //DOUBLE_TO_FLOAT_STRINGSCANNER_H
