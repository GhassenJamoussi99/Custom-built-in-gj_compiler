#include <iostream>
#include <unordered_map>
#include <vector>

#include "scope.h"
#include "log.h"

std::vector<std::unordered_map<std::string, Symbol*>> scope_stack;
int scope_stack_local_var_counts[STACK_MAX];
int scope_stack_parameter_counts[STACK_MAX];

int local_offset = 0;
int param_offset = 16; // Start at 16(%rbp) since 0(%rbp) is return address and 8(%rbp) is saved rbp

void Scope::enter() {
    LOG(INFO) << "Entering new scope.";
    scope_stack.push_back(std::unordered_map<std::string, Symbol*>());
}

void Scope::exit() {
    if (!scope_stack.empty()) {
        LOG(INFO) << "Exiting scope, current level: " << scope_stack.size();
        scope_stack.pop_back();
    } else {
        LOG(ERROR) << "Error: No scope to exit.";
    }
}

int Scope::level() {
    return scope_stack.size();
}

void Scope::bind(std::string name, Symbol *sym) {
    if (scope_stack.empty()) {
        LOG(ERROR) << "Error: No scope to bind symbol to.";
        return;
    }

    // For assembly purposes
    if (sym->kind == SYMBOL_LOCAL) {
        local_offset -= 8; // Allocate space for local variables
        sym->which = local_offset;
        scope_stack_local_var_counts[Scope::level()]++;
    } else if (sym->kind == SYMBOL_PARAM) {
        param_offset += 8; // Assign space for parameters
        sym->which = param_offset;
        scope_stack_parameter_counts[Scope::level()]++;
    }

    LOG(INFO) << "Binding symbol: " << name << " to current scope level: " << Scope::level() << " with offset: " << sym->which;
    scope_stack.back()[name] = sym;
}

Symbol *Scope::lookup(std::string name) {
    for (auto it = scope_stack.rbegin(); it != scope_stack.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            LOG(INFO) << "Symbol: " << name << " found in scope level: " << (scope_stack.rend() - it - 1);
            return found->second;
        }
    }
    LOG(WARN) << "Symbol: " << name << " not found in any scope.";
    return nullptr;
}