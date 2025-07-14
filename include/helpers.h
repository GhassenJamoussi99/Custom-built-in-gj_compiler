#pragma once

std::string indent(int depth);
void print_ast(struct expr *ast, int depth);
void print_stmt(Stmt *s, int depth);
void print_decl_list(Decl *decl_list);
