#include <iostream>
#include <unordered_map>
#include <vector>

#include "scope.h"
#include "log.h"

std::vector<std::unordered_map<std::string, symbol*>> scope_stack;
int scope_stack_local_var_counts[STACK_MAX];
int scope_stack_parameter_counts[STACK_MAX];

int local_offset = 0;
int param_offset = 16; // Start at 16(%rbp) since 0(%rbp) is return address and 8(%rbp) is saved rbp

void scope_enter() {
    LOG(INFO) << "Entering new scope.";
    scope_stack.push_back(std::unordered_map<std::string, symbol*>());
}

void scope_exit() {
    if (!scope_stack.empty()) {
        LOG(INFO) << "Exiting scope, current level: " << scope_stack.size();
        scope_stack.pop_back();
    } else {
        LOG(ERROR) << "Error: No scope to exit.";
        exit(EXIT_FAILURE);
    }
}

int scope_level() {
    return scope_stack.size();
}

void scope_bind(std::string name, struct symbol *sym) {
    if (scope_stack.empty()) {
        LOG(ERROR) << "Error: No scope to bind symbol to.";
        exit(EXIT_FAILURE);
        return;
    }

    // For assembly purposes
    if (sym->kind == SYMBOL_LOCAL) {
        local_offset -= 8; // Allocate space for local variables
        sym->which = local_offset;
        scope_stack_local_var_counts[scope_level()]++;
    } else if (sym->kind == SYMBOL_PARAM) {
        param_offset += 8; // Assign space for parameters
        sym->which = param_offset;
        scope_stack_parameter_counts[scope_level()]++;
    }

    LOG(INFO) << "Binding symbol: " << name << " to current scope level: " << scope_level() << " with offset: " << sym->which;
    scope_stack.back()[name] = sym;
}

struct symbol *scope_lookup(std::string name) {
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