#pragma once

#include <iostream>
#include <string>

class Decl;
class Stmt;
class Symbol;

void decl_codegen(Decl *d);
void stmt_codegen(int depth, Stmt *s);
void expr_codegen(int depth, struct expr *e);
void decl_finish_codegen();
std::string symbol_codegen(Symbol *sym);
