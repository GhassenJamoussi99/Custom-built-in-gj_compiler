#pragma once

class Decl;

void print_type_dot(Type* t);
void print_param_list_dot(struct param_list* params);
void print_ast_dot(struct expr *ast);
void print_stmt_dot(Stmt *s);
void print_decl_list_dot(Decl *decl_list);