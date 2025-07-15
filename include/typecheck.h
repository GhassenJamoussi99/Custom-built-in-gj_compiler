#pragma once

class Decl;
class Stmt;
class Expr;
class Type;

class Typecheck {
public:
    static void decl_typecheck(Decl *d);
    static Type *expr_typecheck(Expr *e);
    static void stmt_typecheck(Stmt *s);
};