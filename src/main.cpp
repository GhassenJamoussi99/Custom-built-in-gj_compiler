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

/** 
 * TODOS:
 * INCREMENT/DECREMENT NOT WORKING CORRECTLY - TO FIX
 * Improve stmt typechecks
 * Improve expr typchecks - EXPR_CALL
 * Switch to smart pointers
 * Classify everything later - 
 * Implement doxygen style for comments
 * evaluate functions successfully
 * "if" statement for stmt 
 * implement while eval, for eval and functions eval
 * organize folder structures
 * When a var is not init it is for some reason considered as \ 
 * An integer, this neeeds to be checked. 
 * Fix seg fault of typecheking example: 
 *  Type error: Comparison '<' requires both operands to be of the same type.
 *  Left operand type: Segmentation fault
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/

