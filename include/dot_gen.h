#pragma once

class Type;
class Expr;
class Stmt;
class Decl;
struct param_list;

class DotGen {
public:
    static void print_type_dot(Type* t);
    static void print_expr_dot(Expr* e);
    static void print_param_list_dot(struct param_list* params);
    static void print_ast_dot(Expr *ast);
    static void print_stmt_dot(Stmt *s);
    static void print_decl_list_dot(Decl *decl_list);
};