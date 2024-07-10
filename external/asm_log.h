#ifndef ASM_LOG_H
#define ASM_LOG_H

#include <iostream>
#include <string>
#include <fstream>
#include <memory>

struct AsmLogConfig {
    AsmLogConfig() {
        std::ofstream clearFile;
        clearFile.open(filePath, std::ios::out | std::ios::trunc);
        clearFile.close();
    }
    std::string filePath = "asm.s";
};

extern AsmLogConfig ASM_LOGCFG;

class AsmLog {
public:
    AsmLog() {
        outfile.open(ASM_LOGCFG.filePath, std::ios::out | std::ios::app);
        multiout = std::make_shared<std::ostream>(outfile.rdbuf());
    }
    ~AsmLog() {
        if (opened) {
            *multiout << std::endl;
            outfile.close();
        }
        opened = false;
    }
    template<typename T>
    AsmLog &operator<<(const T &msg) {
        *multiout << msg;
        opened = true;
        return *this;
    }

private:
    bool opened = false;
    std::ofstream outfile;
    std::shared_ptr<std::ostream> multiout;
};

#endif // ASM_LOG_H
