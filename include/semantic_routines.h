#pragma once

#include "expr.h"
#include "decl.h"

void constant_fold_expr(struct expr *ast);
void constant_fold_stmt(Stmt *statement);
void constant_fold_decls(Decl *decl_list);

/*
  TODO ADD EXPR_CALLS, FOR LOOP, WHILE
 */