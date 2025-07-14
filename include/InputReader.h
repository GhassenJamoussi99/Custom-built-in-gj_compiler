#pragma once

#include <string>

class InputReader {
    public:
        InputReader(const std::string& filename);
        ~InputReader();
        bool openFile();
        void closeFile();
    private:
        std::string filename;
};
