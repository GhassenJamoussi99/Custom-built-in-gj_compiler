#pragma once

void decl_typecheck(Decl *d);
Type *expr_typecheck(Expr *e);
void stmt_typecheck(Stmt *s);