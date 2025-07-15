#pragma once

#include <iostream>
#include <string>

class Decl;
class Stmt;
class Symbol;
class Expr;

class IntelCodegen {
public:
    static void decl_codegen(Decl *d);
    static void stmt_codegen(int depth, Stmt *s);
    static void expr_codegen(int depth, Expr *e);
    static void decl_finish_codegen();
    static std::string symbol_codegen(Symbol *sym);
};
