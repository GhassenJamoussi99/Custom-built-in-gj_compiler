#pragma once

void decl_typecheck(struct decl *d);
struct type *expr_typecheck(struct expr *e);
void stmt_typecheck(struct stmt *s);