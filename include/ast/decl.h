#ifndef DECL_H
#define DECL_H

#include <stdio.h>

#include "type.h"
#include "stmt.h"
#include "expr.h"

struct decl {
	std::string name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct decl *next;
	int local_var_count;
};

struct decl * decl_create( std::string name, struct type *type, struct expr *value, struct stmt *code, struct decl *next );
void decl_resolve( struct decl *d );
void decl_typecheck( struct decl *d );

#endif