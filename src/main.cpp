#include <stdio.h>
#include <iostream>

#include "compiler.h"
#include "log.h"
#include "asm_log.h"
#include "dot_log.h"

extern FILE *yyin;
extern int yyparse();

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

    yyin = fopen(argv[1], "r");
    if (!yyin)
    {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    compiler gj_compiler;
    gj_compiler.compile();

    fclose(yyin);
}


/** 
 * DONE:
 * parse functions successfully : done
 * add if else in the parser
 * change bminor code to comply to b-minor of github standards
 * handle simple print
 * for loop
 * consider comments 
 * Implement typechecks
 * Implement resolve 
 * Test with the data from the book
 * Implement semantic routines
 * handle complex print
 * Improve typechecks for expr
 * Implement IR
 * Implmenet codegen
 * good1-8.bminor
 * Consider print in codegen
 * Fix good9.bminor fix if else statements.
 * TEST other standard tests.
 * To improve typechecks
 * --------------------------------------------------------------
 * 
 * TODOS:
 * 
   

 *  
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
 * Add modern C++ methods
 * Switch to full use of classes at the end after following the book
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

