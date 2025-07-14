#include <iostream>
#include <cstdlib>

#include "decl.h"
#include "type.h"
#include "expr.h"
#include "stmt.h"
#include "symbol.h"
#include "scope.h"
#include "scratch.h"

#include "log.h"
#include "asm_log.h"

void decl_typecheck(Decl *d) {
    LOG(INFO) << "decl::decl_typecheck";

    if (!d) return;

    if (d->value) {
        struct type *t;
        t = expr_typecheck(d->value);
        if (!type_equals(t, d->decl_symbol->type)) {
            std::cerr << "Type error: Declaration type does not match the type of the assigned value. Declaration type: " 
                      << type_to_string(d->decl_symbol->type->kind) << ", Assigned value type: " << type_to_string(t->kind) << std::endl;
        }
        type_delete(t);
    }

    if (d->code) {
        param_list_typecheck(d->decl_type->params);
        stmt_typecheck(d->code);
    }

    if (d->next) {
        decl_typecheck(d->next);
    }
}

void stmt_typecheck(struct stmt *s) {
    struct type *t = nullptr;

    if (!s) return;

    switch (s->kind) {
        case STMT_EXPR:
            LOG(INFO) << "stmt_typecheck::STMT_EXPR";
            t = expr_typecheck(s->expr);
            type_delete(t);
            break;

        case STMT_IF_ELSE:
            LOG(INFO) << "stmt_typecheck::STMT_IF_ELSE";
            if (s->expr) {
                t = expr_typecheck(s->expr);
            }

            if (t->kind != TYPE_BOOLEAN) {
                std::cerr << "Type error: IF condition must be of boolean type. Condition type: " << type_to_string(t->kind) << std::endl;
                LOG(ERROR) << "stmt_typecheck::Type error: IF condition must be of boolean type. Condition type: " << type_to_string(t->kind);
                exit(EXIT_FAILURE);
            }

            stmt_typecheck(s->body);
            stmt_typecheck(s->else_body);
            break;

        case STMT_WHILE:
            LOG(INFO) << "stmt_typecheck::STMT_WHILE";
            t = expr_typecheck(s->expr);
            if (t->kind != TYPE_BOOLEAN) {
                std::cerr << "Type error: WHILE condition must be of boolean type. Condition type: " << t->kind << std::endl;
                LOG(ERROR) << "stmt_typecheck::Type error: WHILE condition must be of boolean type. Condition type: " << t->kind;
                exit(EXIT_FAILURE);
            }
            type_delete(t);
            stmt_typecheck(s->body);
            break;

        case STMT_PRINT:
            LOG(INFO) << "stmt_typecheck::STMT_PRINT";
            //TODO later
            break;

        case STMT_RETURN:
            LOG(INFO) << "stmt_typecheck::STMT_RETURN";
            t = expr_typecheck(s->expr);
            //TODO later
            type_delete(t);
            break;

        case STMT_DECL:
            LOG(INFO) << "stmt_typecheck::STMT_DECL";
            decl_typecheck(s->decl);
            break;

        case STMT_BLOCK:
            LOG(INFO) << "stmt_typecheck::STMT_BLOCK";
            for (struct stmt *curr = s->body; curr != nullptr; curr = curr->next) {
                stmt_typecheck(curr);
            }
            break;

        case STMT_FOR:
            LOG(INFO) << "stmt_typecheck::STMT_FOR";
            if (s->init_expr) {
                t = expr_typecheck(s->init_expr);
                type_delete(t);
            }
            if (s->expr) {
                t = expr_typecheck(s->expr);
                if (t->kind != TYPE_BOOLEAN) {
                    std::cerr << "Type error: FOR loop condition must be of boolean type. Condition type: " << t->kind << std::endl;
                    LOG(ERROR) << "stmt_typecheck::Type error: FOR loop condition must be of boolean type. Condition type: " << t->kind;
                    exit(EXIT_FAILURE);
                }
                type_delete(t);
            }
            if (s->next_expr) {
                t = expr_typecheck(s->next_expr);
                type_delete(t);
            }
            stmt_typecheck(s->body);
            break;

       case STMT_FUNCTION:
            LOG(INFO) << "stmt_typecheck::STMT_FUNCTION";
            if (s->body) {
                stmt_typecheck(s->body);
            } else {
                std::cerr << "Type error: Function declaration or type is null." << std::endl;
                LOG(ERROR) << "stmt_typecheck::Type error: Function declaration or type is null.";
                exit(EXIT_FAILURE);
            }
            break;

        default:
            std::cerr << "stmt_typecheck::Unknown statement type encountered: " << stmt_to_string(s->kind) << std::endl;
            LOG(ERROR) << "stmt_typecheck::Unknown statement type encountered: " << stmt_to_string(s->kind);
            exit(EXIT_FAILURE);
            break;
    }
}

struct type *expr_typecheck(struct expr *e)
{
    LOG(DEBUG) << "expr::expr_typecheck";

    struct type *lt = nullptr;
    struct type *rt = nullptr;
    struct type *result = NULL;

    if (!e) {
        LOG(DEBUG) << "expr_typecheck: Expression is NULL";
        return NULL;
    }

    if (e->left) {
        LOG(DEBUG) << "expr_typecheck: Checking left expression";
        lt = expr_typecheck(e->left);
    }

    if (e->right) {
        LOG(DEBUG) << "expr_typecheck: Checking right expression";
        rt = expr_typecheck(e->right);
    }

    switch (e->kind)
    {
    case EXPR_INTEGER_LITERAL:
        LOG(DEBUG) << "expr_typecheck::EXPR_INTEGER_LITERAL";
        result = type_create(TYPE_INTEGER, NULL, NULL);
        break;
    case EXPR_STRING_LITERAL:
        LOG(DEBUG) << "expr_typecheck::EXPR_STRING_LITERAL";
        result = type_create(TYPE_STRING, NULL, NULL);
        break;
    case EXPR_BOOL_LITERAL:
        LOG(DEBUG) << "expr_typecheck::EXPR_BOOL_LITERAL";
        result = type_create(TYPE_BOOLEAN, NULL, NULL);
        break;
    case EXPR_NAME:
        LOG(DEBUG) << "expr_typecheck::EXPR_NAME";
        if (e->symbol && e->symbol->type) {
            result = type_copy(e->symbol->type);
        } else {
            std::cerr << "Type error: Undefined symbol '" << e->name << "'\n";
            LOG(ERROR) << "Type error: Undefined symbol '" << e->name << "'";
            exit(EXIT_FAILURE);
        }
        break;    
    case EXPR_ADD:
        LOG(DEBUG) << "expr_typecheck::EXPR_ADD";
        //For now only integers - will be later adapted 
        if (lt->kind != TYPE_INTEGER || rt->kind != TYPE_INTEGER)
        {
            std::cerr << "Type error: Addition requires integer operands. Left operand type: " << lt->kind << ", Right operand type: " << rt->kind << std::endl;
            LOG(ERROR) << "Type error: Addition requires integer operands. Left operand type: " << lt->kind << ", Right operand type: " << rt->kind;
            exit(EXIT_FAILURE);
        }
        result = type_create(TYPE_INTEGER, 0, 0);
        break;
    case EXPR_SUBTRACT:
        LOG(DEBUG) << "expr_typecheck::EXPR_SUBTRACT";
        if (lt->kind != TYPE_INTEGER || rt->kind != TYPE_INTEGER)
        {
            std::cerr << "Type error: Subtraction requires integer operands. Left operand type: " << lt->kind << ", Right operand type: " << rt->kind << std::endl;
            LOG(ERROR) << "Type error: Subtraction requires integer operands. Left operand type: " << lt->kind << ", Right operand type: " << rt->kind;
            exit(EXIT_FAILURE);

        }
        result = type_create(TYPE_INTEGER, 0, 0);
        break;
    case EXPR_EQ:
    case EXPR_NEQ:
    case EXPR_LT:
    case EXPR_LEQ:
    case EXPR_GT:
    case EXPR_GEQ:
        LOG(DEBUG) << "expr_typecheck::Comparison " << expr_to_string(e->kind);
        if (!type_equals(lt, rt))
        {
            std::cerr << "Type error: Comparison '" << expr_to_string(e->kind) << "' requires both operands to be of the same type. Left operand type: " << type_to_string(lt->kind) << ", Right operand type: " << type_to_string(rt->kind) << std::endl;
            LOG(ERROR) << "Type error: Comparison '" << expr_to_string(e->kind) << "' requires both operands to be of the same type. Left operand type: " << type_to_string(lt->kind) << ", Right operand type: " << type_to_string(rt->kind);
            exit(EXIT_FAILURE);
        }
        if (lt->kind == TYPE_VOID || lt->kind == TYPE_FUNCTION)
        {
            std::cerr << "Type error: Comparison cannot be applied to void or function types. Operand type: " << type_to_string(lt->kind) << std::endl;
            LOG(ERROR) << "Type error: Comparison cannot be applied to void or function types. Operand type: " << type_to_string(lt->kind);
            exit(EXIT_FAILURE);
        }
        result = type_create(TYPE_BOOLEAN, NULL, NULL);
        break;

    case EXPR_MULTIPLY:
        LOG(DEBUG) << "expr_typecheck::EXPR_MULTIPLY";
        if (lt->kind != TYPE_INTEGER || rt->kind != TYPE_INTEGER)
        {
            std::cerr << "Type error: Multiplication requires integer operands. Left operand type: " << lt->kind << ", Right operand type: " << rt->kind << std::endl;
            LOG(ERROR) << "Type error: Multiplication requires integer operands. Left operand type: " << lt->kind << ", Right operand type: " << rt->kind;
            exit(EXIT_FAILURE);
        }
        result = type_create(TYPE_INTEGER, NULL, NULL);
        break;

    case EXPR_DIVIDE:
        LOG(DEBUG) << "expr_typecheck::EXPR_DIVIDE";
        if (lt->kind != TYPE_INTEGER || rt->kind != TYPE_INTEGER)
        {
            std::cerr << "Type error: Division requires integer operands. Left operand type: " << lt->kind << ", Right operand type: " << rt->kind << std::endl;
            LOG(ERROR) << "Type error: Division requires integer operands. Left operand type: " << lt->kind << ", Right operand type: " << rt->kind;
            exit(EXIT_FAILURE);
        }
        result = type_create(TYPE_INTEGER, NULL, NULL);
        break;
    case EXPR_CALL:
        LOG(DEBUG) << "expr_typecheck::EXPR_CALL";
        if (lt->kind != TYPE_FUNCTION)
        {
            std::cerr << "Type error: Attempt to call a non-function type. "
                    << "Expression type: " << type_to_string(lt->kind) << std::endl;
            LOG(ERROR) << "Type error: Attempt to call a non-function type. Expression type: " << type_to_string(lt->kind);
            type_delete(lt);
            type_delete(rt);
            exit(EXIT_FAILURE);
            return NULL;
        }
        result = type_copy(lt->subtype);
        break;
    case EXPR_ARG:
        result = type_copy(lt);
        break;
    case EXPR_ASSIGN:
        LOG(DEBUG) << "expr_typecheck::EXPR_ASSIGN";
        if (!type_equals(lt, rt)) {
            std::cerr << "Type error: Assignment types do not match. Left type: " << type_to_string(lt->kind) << ", Right type: " << type_to_string(rt->kind) << std::endl;
            LOG(ERROR) << "Type error: Assignment types do not match. Left type: " << type_to_string(lt->kind) << ", Right type: " << type_to_string(rt->kind);
            std::exit(EXIT_FAILURE);
        }
        result = type_copy(lt);
        break;   
    default:
        std::cerr << "Error: Unhandled expression kind " << expr_to_string(e->kind) << "\n";
        LOG(ERROR) << "Error: Unhandled expression kind " << expr_to_string(e->kind);
        exit(EXIT_FAILURE);
        break;
    }

    type_delete(lt);
    type_delete(rt);
    return result;
}
