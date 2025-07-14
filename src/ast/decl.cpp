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

Decl::Decl(const std::string& name, type* type, expr* value, stmt* code, Decl* next)
    : name(name), decl_type(type), value(value), code(code), decl_symbol(nullptr), next(next), local_var_count(0)
{}

void Decl::resolve() {
    Decl* d = this;
    while (d) {
        LOG(INFO) << "Resolving declaration: " << d->name;
        symbol_t kind = scope_level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
        d->decl_symbol = symbol_create(kind, d->decl_type, d->name);
        expr_resolve(d->value);
        scope_bind(d->name, d->decl_symbol);
        if (d->code) {
            scope_enter();
            param_list* params = d->decl_type->params;
            while (params) {
                LOG(INFO) << "Resolving parameter: " << params->name;
                symbol* param_symbol = symbol_create(SYMBOL_PARAM, params->type, params->name);
                scope_bind(params->name, param_symbol);
                params = params->next;
            }
            stmt_resolve(d->code);
            d->local_var_count = scope_stack_local_var_counts[scope_level()];
            LOG(INFO) << "Number of local variables " << d->local_var_count;
            scope_exit();
        }
        d = d->next;
    }
}

void Decl::typecheck() {
    //TODO
}
