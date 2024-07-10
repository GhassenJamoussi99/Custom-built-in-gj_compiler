#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <memory>

using namespace std;

enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

struct structlog {
    structlog(){
        ofstream clearFile;
        clearFile.open("logs.log", ios::out | ios::trunc);
        clearFile.close();
    };
    typelog level = WARN;
    string filePath = "";
    bool headers = false;
    bool ENABLE = false;
    bool enable_stdout = false; 
};

extern structlog LOGCFG;

class LOG {
public:
    LOG() {}
    LOG(typelog type) : msglevel(type) {
        if (LOGCFG.ENABLE) {
            outfile.open("logs.log", ios::out | ios::app);
            multiout = std::make_shared<ostream>(outfile.rdbuf());
            if (LOGCFG.headers) {
                *multiout << (currentDateTime() + " [" + getLabel(type) + "] ");
                if (LOGCFG.enable_stdout) {
                    cout << (currentDateTime() + " [" + getLabel(type) + "] ");
                }
            }
        }
    }
    ~LOG() {
        if (opened) {
            *multiout << endl;
            if (LOGCFG.enable_stdout) {
                cout << endl;
            }
            outfile.close();
        }
        opened = false;
    }
    template<class T>
    LOG &operator<<(const T &msg) {
        if (msglevel >= LOGCFG.level && LOGCFG.ENABLE) {
            *multiout << msg;
            if (LOGCFG.enable_stdout) {
                cout << msg;
            }
            opened = true;
        }
        return *this;
    }
private:
    bool opened = false;
    typelog msglevel = DEBUG;
    ofstream outfile;
    std::shared_ptr<ostream> multiout;
    inline string getLabel(typelog type) {
        string label;
        switch(type) {
            case DEBUG: label = "DEBUG"; break;
            case INFO:  label = "INFO"; break;
            case WARN:  label = "WARN"; break;
            case ERROR: label = "ERROR"; break;
        }
        return label;
    }
    inline const std::string currentDateTime() {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }
};

#endif  /* LOG_H */
