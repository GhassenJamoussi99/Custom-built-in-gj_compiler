#pragma once

std::string indent(int depth);
void print_ast(Expr *ast, int depth);
void print_stmt(Stmt *s, int depth);
void print_decl_list(Decl *decl_list);
