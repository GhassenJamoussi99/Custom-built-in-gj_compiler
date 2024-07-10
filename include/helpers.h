#pragma once

std::string indent(int depth);
void print_ast(struct expr *ast, int depth);
void print_stmt(struct stmt *s, int depth);
void print_decl_list(struct decl *decl_list);
