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

struct expr *expr_create(expr_t kind,
                         struct expr *left,
                         struct expr *right)
{
    expr *e = new expr;

    if (!e)
    {
        std::cerr << "EXPR Error: Out of memory" << std::endl;
        std::exit(1);
    }

    e->kind = kind;
    e->left = left;
    e->right = right;
    e->symbol = nullptr;
    e->type = nullptr;
    e->name = "";
    e->literal_value = 0;
    e->char_literal = '\0';
    e->string_literal = "";
    e->boolean_literal = false;
    e->reg = 0;

    return e;
}

struct expr *expr_create_name(const std::string n)
{
    struct expr *e = expr_create(EXPR_NAME, 0, 0);
    e->name = n;
    return e;
}

struct expr *expr_create_integer_literal(int c)
{
    struct expr *e = expr_create(EXPR_INTEGER_LITERAL, 0, 0);
    e->literal_value = c;
    return e;
}

struct expr *expr_create_boolean_literal(bool status)
{
    struct expr *e = expr_create(EXPR_BOOL_LITERAL, 0, 0);
    e->boolean_literal = status;
    return e;
}

struct expr *expr_create_char_literal(char c)
{
    struct expr *e = expr_create(EXPR_CHAR_LITERAL, 0, 0);
    e->char_literal = c;
    return e;
}

struct expr *expr_create_string_literal(const std::string n)
{
    struct expr *e = expr_create(EXPR_STRING_LITERAL, 0, 0);
    e->string_literal = n;
    return e;
}

int expr_evaluate(struct expr *e)
{
    if (!e)
        return 0;

    int l = expr_evaluate(e->left);
    int r = expr_evaluate(e->right);

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

struct expr *expr_list_create(struct expr *e)
{
    return expr_create(EXPR_ARG, e, nullptr);
}

struct expr *expr_list_append(struct expr *list, struct expr *e)
{
    struct expr *temp = list;
    while (temp->right)
    {
        temp = temp->right;
    }
    temp->right = expr_list_create(e);
    return list;
}

void expr_resolve(struct expr *e)
{
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
            LOG(INFO) << "Resolving left expression of kind: " << expr_to_string(e->kind);
            expr_resolve(e->left);
        }

        if (e->right)
        {
            LOG(INFO) << "Resolving right expression of kind: " << expr_to_string(e->kind);
            expr_resolve(e->right);
        }
    }
}

std::string expr_to_string(expr_t expr)
{
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
