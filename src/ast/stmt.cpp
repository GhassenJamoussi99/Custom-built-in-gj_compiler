#include <iostream>
#include <cstdlib>

#include "stmt.h"
#include "decl.h"
#include "symbol.h"
#include "log.h"
#include "asm_log.h"
#include "scratch.h"


struct stmt * stmt_create( stmt_t kind, struct decl *decl, struct expr *init_expr, struct expr *expr,
                           struct expr *next_expr,struct stmt *body, struct stmt *else_body, struct stmt *next) {
    stmt *s = new stmt;

    if (!s) {
        std::cerr << "STMT Error: Out of memory" << std::endl;
        std::exit(1);
    }

    s->kind = kind;
    s->decl = decl;
    s->init_expr = init_expr;
    s->expr = expr;
    s->next_expr = next_expr;
    s->body = body;
    s->else_body = else_body;
    s->next = next;

    return s;
}

stmt *stmt_create_if_else(expr *expr, stmt *body, stmt *else_body)
{
    stmt *s = new stmt;

    if (!s) {
        std::cerr << "STMT Error: Out of memory" << std::endl;
        std::exit(1);
    }

    s->kind = STMT_IF_ELSE;
    s->decl = nullptr;
    s->init_expr = nullptr;
    s->expr = expr;
    s->next_expr = nullptr;
    s->body = body;
    s->else_body = else_body;
    s->next = nullptr;

    return s;
}

// Function to append a statement to the statement list
struct stmt *stmt_list_append(struct stmt *list, struct stmt *stmt) {
    if (!list) {
        return stmt;
    }

    struct stmt *current = list;
    while (current->next) {
        current = current->next;
    }
    current->next = stmt;
    return list;
}

void stmt_resolve(struct stmt *s) {
    if (!s) return;

    LOG(INFO) << "stmt_resolve::";

    switch (s->kind) {
        case STMT_DECL:
            LOG(INFO) << "stmt_resolve::Resolving declaration statement";
            decl_resolve(s->decl);
            break;

        case STMT_EXPR:
            LOG(INFO) << "stmt_resolve::Resolving expression statement";
            expr_resolve(s->expr);
            break;

        case STMT_IF_ELSE:
            LOG(INFO) << "stmt_resolve::Resolving if-else statement";
            expr_resolve(s->expr);
            stmt_resolve(s->body);
            stmt_resolve(s->else_body);
            break;

        case STMT_FOR:
            LOG(INFO) << "stmt_resolve::Resolving for loop statement";
            if (s->init_expr) {
                LOG(DEBUG) << "stmt_resolve::Resolving init expression of for loop";
                expr_resolve(s->init_expr);
            } else {
                LOG(DEBUG) << "stmt_resolve::Init expression of for loop is null";
            }
            if (s->expr) {
                LOG(DEBUG) << "stmt_resolve::Resolving condition expression of for loop";
                expr_resolve(s->expr);
            } else {
                LOG(DEBUG) << "stmt_resolve::Condition expression of for loop is null";
            }
            if (s->next_expr) {
                LOG(DEBUG) << "stmt_resolve::Resolving next expression of for loop";
                expr_resolve(s->next_expr);
            } else {
                LOG(DEBUG) << "stmt_resolve::Next expression of for loop is null";
            }
            if (s->body) {
                LOG(DEBUG) << "stmt_resolve::Resolving body of for loop";
                stmt_resolve(s->body);
            } else {
                LOG(DEBUG) << "stmt_resolve::Body of for loop is null";
            }
            break;

        case STMT_PRINT:
            LOG(INFO) << "stmt_resolve::Resolving print statement";
            expr_resolve(s->expr);
            break;

        case STMT_WHILE:
            LOG(INFO) << "stmt_resolve::Resolving while loop statement";
            expr_resolve(s->expr);
            stmt_resolve(s->body);
            break;

        case STMT_RETURN:
            LOG(INFO) << "stmt_resolve::Resolving return statement";
            expr_resolve(s->expr);
            break;

        case STMT_BLOCK:
            LOG(INFO) << "stmt_resolve::Resolving block statement";
            stmt_resolve(s->body);
            break;

        case STMT_FUNCTION:
            LOG(INFO) << "stmt_resolve::Resolving function statement";
            stmt_resolve(s->body);
            break;

        default:
            LOG(ERROR) << "stmt_resolve::Unknown statement type encountered." << stmt_to_string(s->kind);
            exit(EXIT_FAILURE);
            break;
    }

    if (s->next) {
        LOG(INFO) << "stmt_resolve::Resolving next statement in the list";
        stmt_resolve(s->next);
    }
}

std::string stmt_to_string(stmt_t kind) {
    switch (kind) {
        case STMT_DECL:
            return "STMT_DECL";
        case STMT_EXPR:
            return "STMT_EXPR";
        case STMT_IF_ELSE:
            return "STMT_IF_ELSE";
        case STMT_FOR:
            return "STMT_FOR";
        case STMT_PRINT:
            return "STMT_PRINT";
        case STMT_WHILE:
            return "STMT_WHILE";
        case STMT_FUNCTION:
            return "STMT_FUNCTION";
        case STMT_RETURN:
            return "STMT_RETURN";
        case STMT_BLOCK:
            return "STMT_BLOCK";
        default:
            return "UNKNOWN_STATEMENT_KIND";
    }
}
