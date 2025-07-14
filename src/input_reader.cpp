#include "input_reader.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

// @brief Declare yyin for Flex/Bison compatibility
// @note This is a global variable declared in the generated parser.cpp file
extern FILE *yyin;

InputReader::InputReader(const std::string& filename) : filename(filename) {}

InputReader::~InputReader() {
    this->closeFile();
}

bool InputReader::openFile() {
    // Open with FILE* for Flex/Bison compatibility
    yyin = fopen(filename.c_str(), "r");
    if (!yyin) {
        fclose(yyin);
        return false;
    }
    return true;
}

void InputReader::closeFile() {
    fclose(yyin);
}
