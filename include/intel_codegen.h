#pragma once

#include <iostream>
#include <string>

void decl_codegen(struct decl *d);
void stmt_codegen(int depth, struct stmt *s);
void expr_codegen(int depth, struct expr *e);
void decl_finish_codegen();
std::string symbol_codegen(struct symbol *sym);
