#ifndef SYMBOL_H
#define SYMBOL_H

class Type;

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
	Type *type;
	std::string name;
	int which;
	int param_count;

	Symbol(symbol_t kind, Type *type, std::string name);
	static std::string to_string(symbol_t symbol);
};

#endif