#pragma once

void decl_typecheck(Decl *d);
Type *expr_typecheck(struct expr *e);
void stmt_typecheck(Stmt *s);