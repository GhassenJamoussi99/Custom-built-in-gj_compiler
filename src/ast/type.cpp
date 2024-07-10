#include "type.h"
#include <iostream>
#include <string>
#include <cstdlib>


struct type * type_create(type_t kind, struct type *subtype, struct param_list *params) {
    struct type *t = new struct type;

    if (!t) {
        std::cerr << "TYPE Error: Out of memory" << std::endl;
        std::exit(1);
    }

    t->kind = kind;
    t->subtype = subtype;
    t->params = params;
    return t;
}

std::string type_to_string(type_t type) {
    switch (type) {
        case TYPE_VOID:
            return "TYPE_VOID";
        case TYPE_BOOLEAN:
            return "TYPE_BOOLEAN";
        case TYPE_CHARACTER:
            return "TYPE_CHARACTER";
        case TYPE_INTEGER:
            return "TYPE_INTEGER";
        case TYPE_STRING:
            return "TYPE_STRING";
        case TYPE_FUNCTION:
            return "TYPE_FUNCTION";
        default:
            return "unknown";
    }
}

bool param_list_equals(struct param_list *a, struct param_list *b) {
    while (a && b) {
        if (!type_equals(a->type, b->type) || (a->name != b->name)) {
            return false;
        }
        a = a->next;
        b = b->next;
    }
    return a == b; // Both should be nullptr if equal
}

bool type_equals(struct type *a, struct type *b) {
    if (a == b) return true;
    if (a == nullptr || b == nullptr) return false;
    if (a->kind != b->kind) return false;

    switch (a->kind) {
        case TYPE_VOID:
        case TYPE_BOOLEAN:
        case TYPE_CHARACTER:
        case TYPE_INTEGER:
        case TYPE_STRING:
            return true;

        case TYPE_FUNCTION:
            return type_equals(a->subtype, b->subtype) && param_list_equals(a->params, b->params);

        default:
            return false;
    }
}

struct param_list *param_list_copy(struct param_list *p) {
    if (!p) return nullptr;

    struct param_list *copy = new struct param_list;
    if (!copy) {
        std::cerr << "PARAM_LIST Error: Out of memory" << std::endl;
        std::exit(1);
    }

    copy->name = p->name;
    copy->type = type_copy(p->type);
    copy->next = param_list_copy(p->next);

    return copy;
}

struct type *type_copy(struct type *t) {
    if (!t) return nullptr;

    struct type *copy = new struct type;
    if (!copy) {
        std::cerr << "TYPE Error: Out of memory" << std::endl;
        std::exit(1);
    }

    copy->kind = t->kind;
    copy->subtype = type_copy(t->subtype);
    copy->params = param_list_copy(t->params);

    return copy;
}

void param_list_delete(struct param_list *p) {
    while (p) {
        struct param_list *next = p->next;
        delete p->type;
        delete p;
        p = next;
    }
}

void type_delete(struct type *t) {
    if (!t) return;

    type_delete(t->subtype);
    param_list_delete(t->params);

    delete t;
}
