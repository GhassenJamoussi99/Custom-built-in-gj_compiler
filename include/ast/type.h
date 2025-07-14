#ifndef TYPE_H
#define TYPE_H

#include <array>
#include <string>

// Forward declaration
struct param_list;

typedef enum {
	TYPE_VOID,
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_FUNCTION
} type_t;

class Type {
public:
	type_t kind;
	Type *subtype;
	struct param_list *params;

	Type(type_t kind, Type *subtype, struct param_list *params);
	static Type* create(type_t kind, Type *subtype, struct param_list *params);
	static bool equals(Type *a, Type *b);
	static Type* copy(Type *t);
	static void delete_type(Type *t);
	static std::string to_string(type_t type);
};

// Legacy functions for backward compatibility
Type* type_create(type_t kind, Type *subtype, struct param_list *params);
bool type_equals(Type *a, Type *b);
Type* type_copy(Type *t);
void type_delete(Type *t);
std::string type_to_string(type_t type);

#endif