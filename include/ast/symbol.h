#ifndef SYMBOL_H
#define SYMBOL_H

#include "type.h"

#include <string>
#include <iostream>

typedef enum {
	SYMBOL_LOCAL,
	SYMBOL_PARAM,
	SYMBOL_GLOBAL
} symbol_t;

class Symbol {
public:
	symbol_t kind;
	struct type *type;
	std::string name;
	int which;
	int param_count;

	Symbol(symbol_t kind, struct type *type, std::string name);
	static std::string to_string(symbol_t symbol);
};

// Legacy function for backward compatibility
Symbol* symbol_create(symbol_t kind, struct type *type, std::string name);
std::string symbol_to_string(symbol_t symbol);

#endif