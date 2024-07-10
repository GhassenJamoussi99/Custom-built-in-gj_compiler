#include <unordered_map>
#include <vector>

#include "log.h"
#include "symbol.h"
#include "scope.h"

struct symbol *symbol_create(symbol_t kind, struct type *type, std::string name) {

    std::string kind_str = symbol_to_string(kind);
    LOG(INFO) << "Creating symbol: " << name << " of kind: " << kind_str;
    symbol *sym = new symbol;
    sym->kind = kind;
    sym->type = type;
    sym->name = name;
    sym->which = 0;
    sym->param_count = 0;
    return sym;
}

std::string symbol_to_string(symbol_t symbol) {
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