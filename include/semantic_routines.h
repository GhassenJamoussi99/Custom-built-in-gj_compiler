#pragma once

#include "expr.h"
#include "decl.h"

class Expr;
class Stmt;
class Decl;

class SemanticRoutines {
public:
    static void constant_fold_expr(Expr *ast);
    static void constant_fold_stmt(Stmt *statement);
    static void constant_fold_decls(Decl *decl_list);
};

/*
  TODO ADD EXPR_CALLS, FOR LOOP, WHILE
 */