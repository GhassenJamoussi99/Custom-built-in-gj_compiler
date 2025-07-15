#include <stdio.h>
#include <iostream>

#include "compiler.h"
#include "log.h"
#include "asm_log.h"
#include "dot_log.h"

#include "input_reader.h"

using namespace std;

structlog LOGCFG = {}; //should be defined once
AsmLogConfig ASM_LOGCFG;
DotLogConfig DOT_LOGCFG;

int main(int argc, char *argv[])
{
    //setup logger for debugging
    LOGCFG.headers = true; 
    LOGCFG.ENABLE = true;
    LOGCFG.enable_stdout = false;
    LOGCFG.level = DEBUG;

    LOG(INFO) << "Starting compiler...";
    
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    const std::string filename = argv[1];
    InputReader inputReader(filename);
    if (!inputReader.openFile())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }   

    compiler gj_compiler;
    gj_compiler.compile();
}