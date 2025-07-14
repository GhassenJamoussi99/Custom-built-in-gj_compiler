#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "expr.h"
#include "symbol.h"
#include "scratch.h"
#include "scope.h"
#include "log.h"

#include "asm_log.h"

Expr::Expr(expr_t kind, Expr *left, Expr *right)
    : kind(kind), left(left), right(right), symbol(nullptr), type(nullptr), 
      name(""), literal_value(0), char_literal('\0'), string_literal(""), 
      boolean_literal(false), reg(0) {
}

Expr* Expr::create(expr_t kind, Expr *left, Expr *right) {
    return new Expr(kind, left, right);
}

Expr* Expr::create_name(const std::string n) {
    Expr *e = create(EXPR_NAME, nullptr, nullptr);
    e->name = n;
    return e;
}

Expr* Expr::create_integer_literal(int c) {
    Expr *e = create(EXPR_INTEGER_LITERAL, nullptr, nullptr);
    e->literal_value = c;
    return e;
}

Expr* Expr::create_boolean_literal(bool status) {
    Expr *e = create(EXPR_BOOL_LITERAL, nullptr, nullptr);
    e->boolean_literal = status;
    return e;
}

Expr* Expr::create_char_literal(char c) {
    Expr *e = create(EXPR_CHAR_LITERAL, nullptr, nullptr);
    e->char_literal = c;
    return e;
}

Expr* Expr::create_string_literal(const std::string n) {
    Expr *e = create(EXPR_STRING_LITERAL, nullptr, nullptr);
    e->string_literal = n;
    return e;
}

int Expr::evaluate(Expr *e) {
    if (!e)
        return 0;

    int l = evaluate(e->left);
    int r = evaluate(e->right);

    switch (e->kind)
    {
    case EXPR_INTEGER_LITERAL:
        return e->literal_value;
    case EXPR_ADD:
        return l + r;
    case EXPR_SUBTRACT:
        return l - r;
    case EXPR_MULTIPLY:
        return l * r;
    case EXPR_DIVIDE:
        if (r == 0)
        {
            printf("error: divide by zero\n");
            exit(1);
        }
        return l / r;
    case EXPR_CALL:
        std::cout << "EXPR_CALL " << e->kind << std::endl;
        break;
    case EXPR_CHAR_LITERAL:
    case EXPR_BOOL_LITERAL:
    case EXPR_STRING_LITERAL:
    case EXPR_EQ:
        return l == r;
    case EXPR_NEQ:
        return l != r;
    case EXPR_LT:
        return l < r;
    case EXPR_GT:
        return l > r;
    case EXPR_LEQ:
        return l <= r;
    case EXPR_GEQ:
        return l >= r;
    default:
        std::cerr << "error: unknown expression type: " << e->kind << std::endl;
        std::exit(1);
    }

    return 0;
}

Expr* Expr::list_create(Expr *e) {
    return create(EXPR_ARG, e, nullptr);
}

Expr* Expr::list_append(Expr *list, Expr *e) {
    Expr *temp = list;
    while (temp->right)
    {
        temp = temp->right;
    }
    temp->right = list_create(e);
    return list;
}

void Expr::resolve(Expr *e) {
    LOG(INFO) << "expr::expr_resolve";

    if (!e)
        return;
    if (e->kind == EXPR_NAME)
    {
        e->symbol = scope_lookup(e->name);
        e->type = e->symbol->type;
    }
    else
    {
        if (e->left)
        {
            LOG(INFO) << "Resolving left expression of kind: " << to_string(e->kind);
            resolve(e->left);
        }

        if (e->right)
        {
            LOG(INFO) << "Resolving right expression of kind: " << to_string(e->kind);
            resolve(e->right);
        }
    }
}

std::string Expr::to_string(expr_t expr) {
    switch (expr)
    {
    case EXPR_ADD:
        return "EXPR_ADD";
    case EXPR_SUBTRACT:
        return "EXPR_SUBTRACT";
    case EXPR_DIVIDE:
        return "EXPR_DIVIDE";
    case EXPR_CALL:
        return "EXPR_CALL";
    case EXPR_ARG:
        return "EXPR_ARG";
    case EXPR_MULTIPLY:
        return "EXPR_MULTIPLY";
    case EXPR_NAME:
        return "EXPR_NAME";
    case EXPR_ASSIGN:
        return "EXPR_ASSIGN";
    case EXPR_INTEGER_LITERAL:
        return "EXPR_INTEGER_LITERAL";
    case EXPR_CHAR_LITERAL:
        return "EXPR_CHAR_LITERAL";
    case EXPR_BOOL_LITERAL:
        return "EXPR_BOOL_LITERAL";
    case EXPR_STRING_LITERAL:
        return "EXPR_STRING_LITERAL";
    case EXPR_EQ:
        return "EXPR_EQ";
    case EXPR_NEQ:
        return "EXPR_NEQ";
    case EXPR_LT:
        return "EXPR_LT";
    case EXPR_GT:
        return "EXPR_GT";
    case EXPR_LEQ:
        return "EXPR_LEQ";
    case EXPR_GEQ:
        return "EXPR_GEQ";
    default:
        return "UNKNOWN_EXPR";
    }
}

// Legacy functions for backward compatibility
Expr* expr_create(expr_t kind, Expr *left, Expr *right) {
    return Expr::create(kind, left, right);
}

Expr* expr_create_name(const std::string n) {
    return Expr::create_name(n);
}

Expr* expr_create_integer_literal(int c) {
    return Expr::create_integer_literal(c);
}

Expr* expr_create_boolean_literal(bool status) {
    return Expr::create_boolean_literal(status);
}

Expr* expr_create_char_literal(char c) {
    return Expr::create_char_literal(c);
}

Expr* expr_create_string_literal(const std::string n) {
    return Expr::create_string_literal(n);
}

Expr* expr_list_create(Expr *e) {
    return Expr::list_create(e);
}

Expr* expr_list_append(Expr *list, Expr *e) {
    return Expr::list_append(list, e);
}

std::string expr_to_string(expr_t expr) {
    return Expr::to_string(expr);
}

int expr_evaluate(Expr *e) {
    return Expr::evaluate(e);
}

void expr_resolve(Expr *e) {
    Expr::resolve(e);
}
