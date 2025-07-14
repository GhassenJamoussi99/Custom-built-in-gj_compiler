#ifndef EXPR_H
#define EXPR_H

#include <string>

class Symbol;
class Type;

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

class Expr {
public:
	/* used by all kinds of exprs */
	expr_t kind;
	Expr *left;
	Expr *right;
    Symbol *symbol;
	Type *type;

	/* used by various leaf exprs */
	std::string name;
	int literal_value;
	char char_literal;
	std::string string_literal;
	bool boolean_literal;

	int reg; // Register allocated for this expression

	Expr(expr_t kind, Expr *left, Expr *right);
	static Expr* create(expr_t kind, Expr *left, Expr *right);
	static Expr* create_name(const std::string n);
	static Expr* create_integer_literal(int c);
	static Expr* create_boolean_literal(bool status);
	static Expr* create_char_literal(char c);
	static Expr* create_string_literal(const std::string n);
	static Expr* list_create(Expr *e);
	static Expr* list_append(Expr *list, Expr *e);
	static std::string to_string(expr_t expr);
	static int evaluate(Expr *e);
	static void resolve(Expr *e);
};

// Legacy functions for backward compatibility
Expr* expr_create(expr_t kind, Expr *left, Expr *right);
Expr* expr_create_name(const std::string n);
Expr* expr_create_integer_literal(int c);
Expr* expr_create_boolean_literal(bool status);
Expr* expr_create_char_literal(char c);
Expr* expr_create_string_literal(const std::string n);
Expr* expr_list_create(Expr *e);
Expr* expr_list_append(Expr *list, Expr *e);
std::string expr_to_string(expr_t expr);
int expr_evaluate(Expr *e);
void expr_resolve(Expr *e);
Type *expr_typecheck(Expr *e);

#endif

