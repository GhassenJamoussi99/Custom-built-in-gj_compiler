#include "semantic_routines.h"
#include "log.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>

void constant_fold_expr(struct expr *ast)
{
    if (!ast)
    {
        LOG(DEBUG) << "Encountered null AST node.";
        return;
    }

    LOG(DEBUG) << "Folding node of kind: " << expr_to_string(ast->kind);

    // Recursively fold constants in the left and right subtrees
    if (ast->left)
    {
        LOG(DEBUG) << "Folding left child of node kind: " << expr_to_string(ast->kind)
                   << " with value: " << ast->literal_value << " with name: " << ast->name;
        constant_fold_expr(ast->left);
    }
    else
    {
        LOG(DEBUG) << "Left child of node kind: " << expr_to_string(ast->kind) << " is null.";
    }

    if (ast->right)
    {
        LOG(DEBUG) << "Folding right child of node kind: " << expr_to_string(ast->kind)
                   << " with value: " << ast->literal_value;
        constant_fold_expr(ast->right);
    }
    else
    {
        LOG(DEBUG) << "Right child of node kind: " << expr_to_string(ast->kind) << " is null.";
    }

    // Perform constant folding if both children are value nodes
    if (ast->left && ast->right &&
        ast->left->kind == EXPR_INTEGER_LITERAL &&
        ast->right->kind == EXPR_INTEGER_LITERAL)
    {
        LOG(DEBUG) << "Folding constant operation: " << expr_to_string(ast->kind);
        switch (ast->kind)
        {
            case EXPR_ASSIGN:
                ast->kind = EXPR_INTEGER_LITERAL;
                ast->literal_value = ast->right->literal_value;
                LOG(DEBUG) << "Folded EXPR_ASSIGN: " << ast->left->name << " = " << ast->right->literal_value;
                ast->left = ast->right = nullptr;
                break;
            case EXPR_ADD:
                ast->kind = EXPR_INTEGER_LITERAL;
                ast->literal_value = ast->left->literal_value + ast->right->literal_value;
                LOG(DEBUG) << "Folded EXPR_ADD: " << ast->left->literal_value << " + " << ast->right->literal_value << " = " << ast->literal_value;
                ast->left = ast->right = nullptr;
                break;
            case EXPR_SUBTRACT:
                ast->kind = EXPR_INTEGER_LITERAL;
                ast->literal_value = ast->left->literal_value - ast->right->literal_value;
                LOG(DEBUG) << "Folded EXPR_SUBTRACT: " << ast->left->literal_value << " - " << ast->right->literal_value << " = " << ast->literal_value;
                ast->left = ast->right = nullptr;
                break;
            case EXPR_MULTIPLY:
                ast->kind = EXPR_INTEGER_LITERAL;
                ast->literal_value = ast->left->literal_value * ast->right->literal_value;
                LOG(DEBUG) << "Folded EXPR_MULTIPLY: " << ast->left->literal_value << " * " << ast->right->literal_value << " = " << ast->literal_value;
                ast->left = ast->right = nullptr;
                break;
            case EXPR_DIVIDE:
                if (ast->right->literal_value != 0)
                { // Avoid division by zero
                    ast->kind = EXPR_INTEGER_LITERAL;
                    ast->literal_value = ast->left->literal_value / ast->right->literal_value;
                    LOG(DEBUG) << "Folded EXPR_DIVIDE: " << ast->left->literal_value << " / " << ast->right->literal_value << " = " << ast->literal_value;
                    ast->left = ast->right = nullptr;
                } else {
                    LOG(ERROR) << "Division by zero encountered.";
                    exit(EXIT_FAILURE);
                }
                break;

            default:
                LOG(ERROR) << "constant_fold_expr::Unknown EXPR type encountered: " << expr_to_string(ast->kind) << " " << ast->name;
                exit(EXIT_FAILURE);
                break;
        }
    }
}


void constant_fold_stmt(Stmt *statement)
{
    if (!statement)
    {
        LOG(DEBUG) << "Encountered null statement node.";
        return;
    }

    LOG(DEBUG) << "Folding statement of kind: " << Stmt::to_string(statement->kind);

    switch (statement->kind)
    {
        case STMT_DECL:
            if (statement->decl)
            {
                LOG(DEBUG) << "Folding declaration statement.";
                constant_fold_decls(statement->decl);
            }
            break;
        case STMT_EXPR:
        case STMT_IF_ELSE:
            if (statement->expr_value)
            {
                LOG(DEBUG) << "Folding if/if-else condition.";
                constant_fold_expr(statement->expr_value);
            }
            if (statement->body)
            {
                LOG(DEBUG) << "Folding if/if-else body.";
                constant_fold_stmt(statement->body);
            }
            if (statement->else_body)
            {
                LOG(DEBUG) << "Folding else body.";
                constant_fold_stmt(statement->else_body);
            }
            break;
        case STMT_FOR:
            if (statement->init_expr)
            {
                LOG(DEBUG) << "Folding for-loop init expression.";
                constant_fold_expr(statement->init_expr);
            }
            if (statement->expr_value)
            {
                LOG(DEBUG) << "Folding for-loop condition.";
                constant_fold_expr(statement->expr_value);
            }
            if (statement->next_expr)
            {
                LOG(DEBUG) << "Folding for-loop next expression.";
                constant_fold_expr(statement->next_expr);
            }
            if (statement->body)
            {
                LOG(DEBUG) << "Folding for-loop body.";
                constant_fold_stmt(statement->body);
            }
            break;
        case STMT_WHILE:
            if (statement->expr_value)
            {
                LOG(DEBUG) << "Folding while-loop condition.";
                constant_fold_expr(statement->expr_value);
            }
            if (statement->body)
            {
                LOG(DEBUG) << "Folding while-loop body.";
                constant_fold_stmt(statement->body);
            }
            break;
        case STMT_PRINT:
        case STMT_RETURN:
            if (statement->expr_value)
            {
                LOG(DEBUG) << "Folding print/return statement.";
                constant_fold_expr(statement->expr_value);
            }
            break;
        case STMT_FUNCTION:
            if (statement->body)
            {
                LOG(DEBUG) << "Folding function body.";
                constant_fold_stmt(statement->body);
            }
            break;
        case STMT_BLOCK:
            if (statement->body)
            {
                LOG(DEBUG) << "Folding block statement.";
                constant_fold_stmt(statement->body);
            }
            break;
        default:
            LOG(ERROR) << "Unknown statement type encountered: " << statement->kind;
            exit(EXIT_FAILURE);
            break;
    }

    if (statement->next)
    {
        LOG(DEBUG) << "Folding next statement.";
        constant_fold_stmt(statement->next);
    }
}


void constant_fold_decls(Decl* decl_list) {
    for (Decl* d = decl_list; d != nullptr; d = d->next) {
        if (d->code) {
            LOG(DEBUG) << "Folding declaration statements for: " << d->name;
            constant_fold_stmt(d->code);
        }
        if (d->value) {
            LOG(DEBUG) << "Folding declaration expressions: " << d->name;
            constant_fold_expr(d->value);
        } else {
            LOG(DEBUG) << "Declaration " << d->name << " has a null expression.";
        }
    }
}