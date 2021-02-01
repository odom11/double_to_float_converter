//
// Created by ich on 2/1/21.
//

#include "FileScanner.h"

extern FILE* yyin;

FileScanner::FileScanner(const std::string &name) : fileHandler(name, "r") {
    yyin = fileHandler.getPtr();
}

