#pragma once

class Expr;
class Stmt;
class Decl;

class Helpers {
public:
    static std::string indent(int depth);
    static void print_ast(Expr *ast, int depth);
    static void print_stmt(Stmt *s, int depth);
    static void print_decl_list(Decl *decl_list);
};
