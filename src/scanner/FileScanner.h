//
// Created by ich on 2/1/21.
//

#ifndef DOUBLE_TO_FLOAT_FILESCANNER_H
#define DOUBLE_TO_FLOAT_FILESCANNER_H

#include "Scanner.h"
#include "FileHandler.h"

class FileScanner : public Scanner {
public:
    FileScanner(const std::string& name);
private:
    FileHandler fileHandler;
};


#endif //DOUBLE_TO_FLOAT_FILESCANNER_H
