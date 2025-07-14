#include <iostream>
#include <cstdlib>
#include <cstring>

#include "param_list.h"
#include "symbol.h"
#include "scope.h"
#include "log.h"
#include "type.h"

// Function to create a new parameter list node
param_list* param_list_create(std::string name, Type *type, param_list *next) {
    param_list* p = new param_list;
    if (!p) {
        std::cerr << "Error: Out of memory" << std::endl;
        std::exit(1);
    }
    p->name = name;
    p->type = type;
    p->symbol = nullptr;
    p->next = next;
    return p;
}

struct param_list *param_list_append(struct param_list *list, struct param_list *new_param) {
    if (list == nullptr) {
        return new_param;
    }
    struct param_list *current = list;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = new_param;
    return list;
}

void param_list_resolve(struct param_list *p) {
    while (p) {
        LOG(INFO) << "Resolving parameter: " << p->name;

        symbol_t kind = SYMBOL_PARAM;
        p->symbol = new Symbol(kind, p->type, p->name);
        scope_bind(p->name, p->symbol);

        p = p->next;
    }
}

void param_list_typecheck(struct param_list *params) {
    while (params) {
        LOG(INFO) << "Type checking parameter: " << params->name;

        if (params->type == nullptr) {
            std::cerr << "Type error: Parameter '" << params->name << "' has an invalid type (null)." << std::endl;
        } else {
            switch (params->type->kind) {
                case TYPE_VOID:
                    std::cerr << "Type error: Parameter '" << params->name << "' cannot be of type void." << std::endl;
                    break;
                case TYPE_BOOLEAN:
                    LOG(INFO) << "Parameter '" << params->name << "' is of type boolean.";
                    break;
                case TYPE_CHARACTER:
                    LOG(INFO) << "Parameter '" << params->name << "' is of type character.";
                    break;
                case TYPE_INTEGER:
                    LOG(INFO) << "Parameter '" << params->name << "' is of type integer.";
                    break;
                case TYPE_STRING:
                    LOG(INFO) << "Parameter '" << params->name << "' is of type string.";
                    break;
                case TYPE_FUNCTION:
                    std::cerr << "Type error: Parameter '" << params->name << "' cannot be of type function." << std::endl;
                    break;
                default:
                    std::cerr << "Type error: Parameter '" << params->name << "' has an unknown type." << std::endl;
                    break;
            }
        }

        params = params->next;
    }
}
