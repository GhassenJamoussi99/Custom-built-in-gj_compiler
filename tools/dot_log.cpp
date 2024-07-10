#include "dot_log.h"

//DotLogConfig impl
DotLogConfig::DotLogConfig() {
    updateFilePath();
    clearFile();
}

void DotLogConfig::updateFilePath() {
    if (OPTIMIZE_FLAG)
        filePath = "ast_optimized.dot";
    else
        filePath = "ast.dot";
}

void DotLogConfig::clearFile() {
    std::ofstream clearFile;
    clearFile.open(filePath, std::ios::out | std::ios::trunc);
    clearFile.close();
}

void DotLogConfig::initiate() {
    DotLog() << "digraph AST {\n";
    DotLog() << "node [shape=record]\n";
}

void DotLogConfig::finish() {
    DotLog() << "}\n";
}

// DotLog impl
DotLog::DotLog() {
    outfile.open(DOT_LOGCFG.filePath, std::ios::out | std::ios::app);
    multiout = std::make_shared<std::ostream>(outfile.rdbuf());
}

DotLog::~DotLog() {
    if (opened) {
        *multiout << std::endl;
        outfile.close();
    }
    opened = false;
}
