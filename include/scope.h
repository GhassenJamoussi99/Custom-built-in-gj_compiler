#pragma once

#include "symbol.h"

#define STACK_MAX 256

void scope_enter();
void scope_exit();
int scope_level();

struct symbol *scope_lookup( std::string name);
void scope_bind( std::string name, struct symbol *sym );