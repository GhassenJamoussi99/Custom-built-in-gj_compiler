#include <iostream>
#include <cstdlib>

#include "decl.h"
#include "type.h"
#include "expr.h"
#include "stmt.h"
#include "symbol.h"
#include "scope.h"
#include "scratch.h"

#include "log.h"
#include "asm_log.h"

extern int scope_stack_local_var_counts[STACK_MAX];

struct decl *decl_create(std::string name, struct type *type, struct expr *value, struct stmt *code, struct decl *next)
{
    decl *d = new decl;

    if (!d)
    {
        std::cerr << "DECL Error: Out of memory" << std::endl;
        std::exit(1);
    }

    d->name = name;
    d->type = type;
    d->value = value;
    d->code = code;
    d->next = next;
    d->local_var_count = 0;

    return d;
}

// Helper function to print indentation
void print_indent(int indent)
{
    for (int i = 0; i < indent; ++i)
    {
        std::cout << " ";
    }
}

void decl_resolve(struct decl *d) {
    if (!d) return;

    LOG(INFO) << "Resolving declaration: " << d->name;

    symbol_t kind = scope_level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
    d->symbol = symbol_create(kind, d->type, d->name);
    expr_resolve(d->value);
    scope_bind(d->name, d->symbol);

    if (d->code) {
        scope_enter();
        struct param_list *params = d->type->params;
        while (params) {
            LOG(INFO) << "Resolving parameter: " << params->name;
            struct symbol *param_symbol = symbol_create(SYMBOL_PARAM, params->type, params->name);
            scope_bind(params->name, param_symbol);
            params = params->next;
        }
        stmt_resolve(d->code);
        d->local_var_count = scope_stack_local_var_counts[scope_level()];

        LOG(INFO) << "Number of local variables " << d->local_var_count;

        scope_exit();
    }

    decl_resolve(d->next);
}

