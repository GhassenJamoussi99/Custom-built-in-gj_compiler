
#ifndef STMT_H
#define STMT_H

#include "decl.h"

class Decl;
struct expr;

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

class Stmt {
public:
	stmt_t kind;
	Decl *decl;
	expr *init_expr;
	expr *expr_value;
	expr *next_expr;
	Stmt *body;
	Stmt *else_body;
	Stmt *next;

	Stmt(stmt_t kind, Decl *decl, expr *init_expr, expr *expr_value, expr *next_expr, Stmt *body, Stmt *else_body, Stmt *next);
	static Stmt* create_if_else(expr *expr_value, Stmt *body, Stmt *else_body);
	static Stmt* list_append(Stmt *list, Stmt *stmt);
	void resolve();
	void typecheck();
	static std::string to_string(stmt_t kind);
};

#endif