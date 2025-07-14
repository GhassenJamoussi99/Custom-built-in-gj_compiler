#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"
#include <string>

typedef enum
{
	EXPR_ADD = 0,
	EXPR_SUBTRACT,
	EXPR_DIVIDE,
	EXPR_CALL,
	EXPR_MULTIPLY,
	EXPR_ARG,
	EXPR_NAME,
	EXPR_ASSIGN,
	EXPR_INTEGER_LITERAL,
	EXPR_CHAR_LITERAL,
	EXPR_BOOL_LITERAL,
	EXPR_STRING_LITERAL,
	EXPR_EQ,
	EXPR_NEQ,
	EXPR_LT,
	EXPR_GT,
	EXPR_LEQ,
	EXPR_GEQ
} expr_t;

struct expr
{
	/* used by all kinds of exprs */
	expr_t kind;
	struct expr *left;
	struct expr *right;
    Symbol *symbol;
	struct type *type;

	/* used by various leaf exprs */
	std::string name;
	int literal_value;
	char char_literal;
	std::string string_literal;
	bool boolean_literal;

	int reg; // Register allocated for this expression
};

struct expr *expr_create(expr_t kind, struct expr *left, struct expr *right);
struct expr *expr_create_name(const std::string n);
struct expr *expr_create_integer_literal(int c);
struct expr *expr_create_boolean_literal(bool status);
struct expr *expr_create_char_literal(char c);
struct expr *expr_create_string_literal(const std::string n);
struct expr *expr_list_create(struct expr *e);
struct expr *expr_list_append(struct expr *list, struct expr *e);

std::string expr_to_string(expr_t expr);
int expr_evaluate(struct expr *e);
void expr_resolve(struct expr *e);
struct type *expr_typecheck(struct expr *e);

#endif

