
#ifndef STMT_H
#define STMT_H

#include "decl.h"

typedef enum {
	STMT_DECL,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_FOR,
	STMT_PRINT,
	STMT_WHILE,
	STMT_FUNCTION,
	STMT_RETURN,
	STMT_BLOCK
} stmt_t;

struct stmt {
	stmt_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};

struct stmt * stmt_create( stmt_t kind, struct decl *decl, struct expr *init_expr, 
							struct expr *expr, struct expr *next_expr, struct stmt *body,
							struct stmt *else_body, struct stmt *next );

struct stmt* stmt_create_if_else(struct expr *expr, struct stmt *body, struct stmt *else_body);

struct stmt *stmt_list_append(struct stmt *list, struct stmt *stmt);
void stmt_resolve( struct stmt *s);
void stmt_typecheck(struct stmt *s);
std::string stmt_to_string(stmt_t kind);

#endif