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

struct symbol {
	symbol_t kind;
	struct type *type;
	std::string name;
	int which;
	int param_count;
};

struct symbol * symbol_create( symbol_t kind, struct type *type, std::string name );
std::string symbol_to_string(symbol_t symbol);

#endif