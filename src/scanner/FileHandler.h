//
// Created by ich on 2/1/21.
//

#ifndef DOUBLE_TO_FLOAT_FILEHANDLER_H
#define DOUBLE_TO_FLOAT_FILEHANDLER_H

#include <stdio.h>
class FileHandler{
public:
    FileHandler(const std::string& filename, const std::string& access);
    ~FileHandler();
    FILE* getPtr() {return file;}
private:
    FILE* file;
};

#endif //DOUBLE_TO_FLOAT_FILEHANDLER_H
