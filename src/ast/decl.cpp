#include <iostream>
#include <cstdlib>

#include "decl.h"
#include "type.h"
#include "expr.h"
#include "stmt.h"
#include "symbol.h"
#include "scope.h"
#include "scratch.h"
#include "param_list.h"

#include "log.h"
#include "asm_log.h"

extern int scope_stack_local_var_counts[STACK_MAX];

Decl::Decl(const std::string& name, Type* type, Expr* value, Stmt* code, Decl* next)
    : name(name), decl_type(type), value(value), code(code), decl_symbol(nullptr), next(next), local_var_count(0)
{}

void Decl::resolve() {
    Decl* d = this;
    while (d) {
        LOG(INFO) << "Resolving declaration: " << d->name;
        symbol_t kind = Scope::level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
        d->decl_symbol = new Symbol(kind, d->decl_type, d->name);
        expr_resolve(d->value);
        Scope::bind(d->name, d->decl_symbol);
        if (d->code) {
            Scope::enter();
            param_list* params = d->decl_type->params;
            while (params) {
                LOG(INFO) << "Resolving parameter: " << params->name;
                Symbol* param_symbol = new Symbol(SYMBOL_PARAM, params->type, params->name);
                Scope::bind(params->name, param_symbol);
                params = params->next;
            }
            d->code->resolve();
            d->local_var_count = scope_stack_local_var_counts[Scope::level()];
            LOG(INFO) << "Number of local variables " << d->local_var_count;
            Scope::exit();
        }
        d = d->next;
    }
}

void Decl::typecheck() {
    //TODO
}
