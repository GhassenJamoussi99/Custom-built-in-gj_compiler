#include <iostream>

#include "expr.h"
#include "decl.h"
#include "helpers.h"
#include "stmt.h"
#include "log.h"

// Helper function to indent based on depth
std::string indent(int depth)
{
    return std::string(depth * 2, ' ');
}

// Recursive function to print the AST
void print_ast(struct expr *ast, int depth)
{
    if (!ast)
    {
        std::cout << indent(depth) << "(null)" << std::endl;
        return;
    }

    std::cout << indent(depth) << "Node kind: " << expr_to_string(ast->kind);

    // Print value based on node type
    switch (ast->kind)
    {
    case EXPR_INTEGER_LITERAL:
        std::cout << ", Value: " << ast->literal_value;
        break;
    case EXPR_CHAR_LITERAL:
        std::cout << ", Value: " << ast->char_literal;
        break;
    case EXPR_BOOL_LITERAL:
        std::cout << ", Value: " << (ast->boolean_literal ? "true" : "false");
        break;
    case EXPR_STRING_LITERAL:
        std::cout << ", Value: " << ast->string_literal;
        break;
    case EXPR_NAME:
        std::cout << ", Name: " << ast->name;
        break;
    default:
        break;
    }
    std::cout << std::endl;

    // Recursively print left and right children
    if (ast->left)
    {
        print_ast(ast->left, depth + 1);
    }
    else
    {
        std::cout << indent(depth + 1) << "(left child is null)" << std::endl;
    }

    if (ast->right)
    {
        print_ast(ast->right, depth + 1);
    }
    else
    {
        std::cout << indent(depth + 1) << "(right child is null)" << std::endl;
    }
}

// Recursive function to print the AST for statements
void print_stmt(Stmt *s, int depth)
{
    if (!s)
    {
        LOG(DEBUG) << "print_stmt: (null)";
        std::cout << indent(depth) << "(null)" << std::endl;
        return;
    }

    LOG(DEBUG) << "print_stmt: Statement kind: " << Stmt::to_string(s->kind);
    switch (s->kind)
    {
    case STMT_DECL:
        LOG(DEBUG) << "print_stmt: STMT_DECL";
        if (s->decl)
        {
            print_decl_list(s->decl);
        }
        else
        {
            LOG(ERROR) << "print_stmt: STMT_DECL has null decl";
            exit(EXIT_FAILURE);
        }
        break;
    case STMT_EXPR:
        LOG(DEBUG) << "print_stmt: STMT_EXPR";
        print_ast(s->expr_value, depth + 1);
        break;
    case STMT_RETURN:
        LOG(DEBUG) << "print_stmt: STMT_RETURN";
        std::cout << indent(depth) << "Return statement" << std::endl;
        print_ast(s->expr_value, depth + 1);
        break;
    case STMT_IF_ELSE:
        LOG(DEBUG) << "print_stmt: STMT_IF_ELSE";
        std::cout << indent(depth) << "If statement" << std::endl;
        print_ast(s->expr_value, depth + 1);
        print_stmt(s->body, depth + 1);
        if (s->else_body)
        {
            std::cout << indent(depth) << "Else statement" << std::endl;
            print_stmt(s->else_body, depth + 1);
        }
        break;
    case STMT_WHILE:
        LOG(DEBUG) << "print_stmt: STMT_WHILE";
        std::cout << indent(depth) << "While statement" << std::endl;
        print_ast(s->expr_value, depth + 1);
        print_stmt(s->body, depth + 1);
        break;
    case STMT_BLOCK:
        LOG(DEBUG) << "print_stmt: STMT_BLOCK";
        std::cout << indent(depth) << "Block statement" << std::endl;
        for (Stmt *stmt = s->body; stmt != nullptr; stmt = stmt->next)
        {
            print_stmt(stmt, depth + 1);
        }
        break;
    case STMT_FUNCTION:
        LOG(DEBUG) << "print_stmt: STMT_FUNCTION";
        if (s->decl != nullptr)
        {
            std::cout << indent(depth) << "Function declaration: " << s->decl->name << std::endl;
        }
        else
        {
            LOG(ERROR) << "print_stmt: STMT_FUNCTION has null decl or decl->name";
            exit(EXIT_FAILURE);
        }
        print_stmt(s->body, depth + 1);
        break;
    default:
        LOG(ERROR) << "print_stmt: Unknown statement kind: " << Stmt::to_string(s->kind);
        exit(EXIT_FAILURE);
        break;
    }

    if (s->next)
    {
        LOG(DEBUG) << "print_stmt: Moving to next statement";
        print_stmt(s->next, depth);
    }
    else
    {
        LOG(DEBUG) << "print_stmt: No more statements at this level";
    }
}

void print_decl_list(Decl *decl_list)
{
    for (Decl *d = decl_list; d != nullptr; d = d->next)
    {
        std::cout << "Declaration: " << d->name << std::endl;
        if (d->code)
        {
            print_stmt(d->code, 1);
        }
    }
}