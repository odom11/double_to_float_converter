//
// Created by ich on 1/31/21.
//

#include "StringScanner.h"

extern "C"
void yy_scan_string(const char* str);


StringScanner::StringScanner(const std::string &str) : str(str) {
    yy_scan_string(str.c_str());
}

