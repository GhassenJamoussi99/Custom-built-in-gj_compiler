#include "type.h"
#include "param_list.h"
#include <iostream>
#include <string>
#include <cstdlib>

Type::Type(type_t kind, Type *subtype, struct param_list *params)
    : kind(kind), subtype(subtype), params(params) {
}

Type* Type::create(type_t kind, Type *subtype, struct param_list *params) {
    return new Type(kind, subtype, params);
}

std::string Type::to_string(type_t type) {
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
        if (!Type::equals(a->type, b->type) || (a->name != b->name)) {
            return false;
        }
        a = a->next;
        b = b->next;
    }
    return a == b; // Both should be nullptr if equal
}

bool Type::equals(Type *a, Type *b) {
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
            return Type::equals(a->subtype, b->subtype) && param_list_equals(a->params, b->params);

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
    copy->type = Type::copy(p->type);
    copy->next = param_list_copy(p->next);

    return copy;
}

Type* Type::copy(Type *t) {
    if (!t) return nullptr;

    Type *copy = new Type(t->kind, Type::copy(t->subtype), param_list_copy(t->params));
    return copy;
}

void param_list_delete(struct param_list *p) {
    while (p) {
        struct param_list *next = p->next;
        Type::delete_type(p->type);
        delete p;
        p = next;
    }
}

void Type::delete_type(Type *t) {
    if (!t) return;

    Type::delete_type(t->subtype);
    param_list_delete(t->params);

    delete t;
}

// Legacy functions for backward compatibility
Type* type_create(type_t kind, Type *subtype, struct param_list *params) {
    return Type::create(kind, subtype, params);
}

bool type_equals(Type *a, Type *b) {
    return Type::equals(a, b);
}

Type* type_copy(Type *t) {
    return Type::copy(t);
}

void type_delete(Type *t) {
    Type::delete_type(t);
}

std::string type_to_string(type_t type) {
    return Type::to_string(type);
}
