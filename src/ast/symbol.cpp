#include <unordered_map>
#include <vector>

#include "log.h"
#include "symbol.h"
#include "scope.h"
#include "type.h"

Symbol::Symbol(symbol_t kind, Type *type, std::string name) 
    : kind(kind), type(type), name(name), which(0), param_count(0) {
    std::string kind_str = Symbol::to_string(kind);
    LOG(INFO) << "Creating symbol: " << name << " of kind: " << kind_str;
}

std::string Symbol::to_string(symbol_t symbol) {
    switch (symbol) {
        case SYMBOL_LOCAL:
            return "SYMBOL_LOCAL";
        case SYMBOL_PARAM:
            return "SYMBOL_PARAM";
        case SYMBOL_GLOBAL:
            return "SYMBOL_GLOBAL";
        default:
            return "UNKNOWN_SYMBOL";
    }
}

// Legacy function for backward compatibility
Symbol* symbol_create(symbol_t kind, Type *type, std::string name) {
    return new Symbol(kind, type, name);
}

std::string symbol_to_string(symbol_t symbol) {
    return Symbol::to_string(symbol);
}