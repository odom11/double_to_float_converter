//
// Created by ich on 2/1/21.
//
#include <filesystem>
#include "FileHandler.h"

FileHandler::FileHandler(const std::string &filename, const std::string &access) {
    file = fopen(filename.c_str(), access.c_str());
    if (file == nullptr) {
        throw std::runtime_error("error opening file '"  + filename + "'");
    }
}

FileHandler::~FileHandler() {fclose(file);}
