#pragma once

void decl_typecheck(Decl *d);
struct type *expr_typecheck(struct expr *e);
void stmt_typecheck(Stmt *s);