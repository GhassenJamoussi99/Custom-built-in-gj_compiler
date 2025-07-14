#ifndef PARAM_LIST_H
#define PARAM_LIST_H

#include "type.h"
#include "symbol.h"

#include <string>
#include <iostream>

struct expr;
class Symbol;

struct param_list
{
	std::string name;
    struct type *type;
    Symbol *symbol;
    struct param_list *next;
};

struct param_list *param_list_create(std::string name, struct type *type, struct param_list *next);
struct param_list *param_list_append(struct param_list *list, struct param_list *new_param);

void param_list_resolve(struct param_list *a);
void param_list_typecheck(struct param_list *a);

#endif