//
// Created by ich on 1/31/21.
//

#include "StringScanner.h"

extern "C"
void yy_scan_string(const char* str);

extern int column_number, line_number;

StringScanner::StringScanner(const std::string &str) : str(str) {
    yy_scan_string(str.c_str());
}

void StringScanner::incrementLineGlobal(int n) {
    line_number += n;
}
