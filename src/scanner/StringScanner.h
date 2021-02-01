//
// Created by ich on 1/31/21.
//

#ifndef DOUBLE_TO_FLOAT_STRINGSCANNER_H
#define DOUBLE_TO_FLOAT_STRINGSCANNER_H

#include "Scanner.h"

class StringScanner : public Scanner {
public:
    explicit StringScanner(const std::string& str);
    void incrementLineGlobal(int n);
    const std::string& getString() {return str;};
private:
    std::string str;
};


#endif //DOUBLE_TO_FLOAT_STRINGSCANNER_H
