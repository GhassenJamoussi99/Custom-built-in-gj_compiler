#include <iostream>
#include "compiler.h"
#include "token.h"
#include "symbol.h"
#include "scope.h"
#include "asm_log.h"

extern int yyparse();
extern char *yytext;
extern Expr *parser_result;

void compiler::compile() {
    AsmLog() << ".intel_syntax noprefix";
    AsmLog() << "\n.text  # Start the code section";

    // Initialize the global scope
    scope_enter();
    
    // Check whether the given program is standard compliant
    if (yyparse() == 0)
    {
        std::cout << "\033[32mParse successful!\033[0m\n";
    } else {
        std::cout << "\033[31mParse failed.\033[0m\n";
        exit(1);
    }

    // Exit the global scope
    scope_exit();

}