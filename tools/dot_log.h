#ifndef DOT_LOG_H
#define DOT_LOG_H

#include <iostream>
#include <string>
#include <fstream>
#include <memory>

class DotLog;

struct DotLogConfig {
    DotLogConfig();

    void updateFilePath();
    void clearFile();
    void initiate();
    void finish();

    std::string filePath;
    bool OPTIMIZE_FLAG = false;
};

extern DotLogConfig DOT_LOGCFG;

class DotLog {
public:
    DotLog();
    ~DotLog();

    template<typename T>
    DotLog &operator<<(const T &msg) {
        *multiout << msg;
        opened = true;
        return *this;
    }

private:
    bool opened = false;
    std::ofstream outfile;
    std::shared_ptr<std::ostream> multiout;
};

#endif // DOT_LOG_H
