#pragma once

void decl_codegen(Decl *d);
std::string symbol_codegen(struct symbol *sym);
void stmt_codegen(int depth, struct stmt *s);
//void expr_codegen(int depth, struct expr *e);
