
#include <iostream>
#include <sstream>
#include <vector>

#include "code_generator.h"
#include "intel_codegen.h"

#include "expr.h"
#include "stmt.h"
#include "decl.h"

#include "scratch.h"
#include "helpers.h"
#include "symbol.h"

#include "asm_log.h"
#include "log.h"

static int label_count = 0;

std::string create_label() {
    return "L" + std::to_string(label_count++);
}

void decl_codegen(struct decl *d) {
    int depth = 1;

    if (!d) return;

    // Handle the declaration of the variable
    if (d->symbol->kind == SYMBOL_GLOBAL) {        

        if (d->value) {
            AsmLog() << d->name << ":";
            switch (d->value->kind) {
                case EXPR_INTEGER_LITERAL:
                    AsmLog() << "   .quad " << d->value->literal_value;
                    break;
                case EXPR_STRING_LITERAL:
                    AsmLog() << "   .string \"" << d->value->string_literal << "\"";
                    break;
                case EXPR_BOOL_LITERAL:
                    AsmLog() << "   .quad " << (d->value->boolean_literal ? 1 : 0);
                    break;
                //ARRAYS and others
                default:
                    std::cerr << "Unsupported initializer for global variable: " << d->name << std::endl;
                    break;
            }
        } else {
            AsmLog() << "\n.text  # Start the code section\n";
        }
    }

    if (d->symbol->kind == SYMBOL_LOCAL || d->symbol->kind == SYMBOL_PARAM) {
        // Allocate space on the stack
        AsmLog() << indent(depth + 1) << "# Allocate space for local variable " << d->name;
    }

    // If there is an initializer, generate code for it (local variables only)
    if (d->value && (d->symbol->kind == SYMBOL_LOCAL || d->symbol->kind == SYMBOL_PARAM)) {
        expr_codegen(depth + 1, d->value);
        AsmLog() << indent(depth + 1) << "mov qword ptr [" << symbol_codegen(d->symbol) << "], " << scratch_name(d->value->reg);
        scratch_free(d->value->reg);
    }

    // If there is a code block associated with this declaration (e.g., a function definition), generate code for it
    if (d->code) {
        AsmLog() << "\n.globl " << d->name;
        AsmLog() << d->name << ":";
        AsmLog() << indent(depth + 1) << "push rbp";
        AsmLog() << indent(depth + 1) << "mov rbp, rsp";
        // Ensure 16-byte alignment
        AsmLog() << indent(depth + 1) << "sub rsp, 16"; // Align the stack pointer to 16 bytes
        stmt_codegen(depth + 1, d->code);
        AsmLog() << indent(depth + 1) << "leave";
        AsmLog() << indent(depth + 1) << "ret";
    }

    // Recursively handle the next declaration in the list
    decl_codegen(d->next);
}


std::string symbol_codegen(struct symbol *sym)
{
    std::ostringstream oss;
    switch (sym->kind) {
        case SYMBOL_LOCAL:
        case SYMBOL_PARAM:
            oss << "rbp" << sym->which;
            break;
        case SYMBOL_GLOBAL:
            oss << sym->name;
            break;
        default:
            oss << "UNKNOWN_SYMBOL_KIND";
            break;
    }
    return oss.str();
}


void stmt_codegen(int depth, struct stmt *s) {
    if (!s) return;

    switch (s->kind) {
        case STMT_EXPR:
            LOG(DEBUG) << "stmt_codegen::Generating code for STMT_EXPR";
            expr_codegen(depth, s->expr);
            scratch_free(s->expr->reg);
            break;

        case STMT_DECL:
            LOG(DEBUG) << "stmt_codegen::Generating code for STMT_DECL";
            decl_codegen(s->decl);
            break;

        case STMT_RETURN:
            LOG(DEBUG) << "stmt_codegen::Generating code for STMT_RETURN";
            expr_codegen(depth, s->expr);
            AsmLog() << indent(depth) << "mov " << scratch_name(s->expr->reg) << ", rax";
            scratch_free(s->expr->reg);
            break;

        case STMT_IF_ELSE:
            {
                LOG(DEBUG) << "stmt_codegen::Generating code for STMT_IF_ELSE";
                std::string else_label = create_label();
                std::string end_label = create_label();
                expr_codegen(depth, s->expr);
                AsmLog() << indent(depth) << "cmp " << scratch_name(s->expr->reg) << ", 0";
                scratch_free(s->expr->reg);
                AsmLog() << indent(depth) << "je " << else_label;
                stmt_codegen(depth, s->body);
                AsmLog() << indent(depth) << "jmp " << end_label;
                AsmLog() << indent(depth) << else_label << ":";
                stmt_codegen(depth, s->else_body);
                AsmLog() << indent(depth) << end_label << ":";
            }
            break;

        case STMT_WHILE:
            {
                LOG(DEBUG) << "stmt_codegen::Generating code for STMT_WHILE";
                std::string start_label = create_label();
                std::string loop_end_label = create_label();
                AsmLog() << start_label << ":";
                expr_codegen(depth, s->expr);
                AsmLog() << "cmp " << scratch_name(s->expr->reg) << ", 0";
                scratch_free(s->expr->reg);
                AsmLog() << "je " << loop_end_label;
                stmt_codegen(depth, s->body);
                AsmLog() << "jmp " << start_label;
                AsmLog() << loop_end_label << ":";
            }
            break;

        case STMT_BLOCK:
            LOG(DEBUG) << "stmt_codegen::Generating code for STMT_BLOCK";
            stmt_codegen(depth, s->body);
            break;

        case STMT_FUNCTION:
            LOG(DEBUG) << "stmt_codegen::Generating code for STMT_FUNCTION";
            stmt_codegen(depth, s->body);
            break;
            
        default:
            LOG(DEBUG) << "stmt_codegen::Unsupported statement kind: " << s->kind << "";
            break;
    }

    stmt_codegen(depth, s->next);
}



// void expr_codegen(int depth, struct expr *e) {
//     if (!e) return;

//     switch (e->kind) {
//         case EXPR_NAME:
//             LOG(INFO) << "expr_codegen::EXPR_NAME";
//             // e->reg = scratch_alloc();
//             // AsmLog() << indent(depth) << "mov " << scratch_name(e->reg) << ", " << symbol_codegen(e->symbol);
//             // LOG(DEBUG) << indent(depth) << "mov " << scratch_name(e->reg) << ", " << symbol_codegen(e->symbol);
//             break;

//         case EXPR_INTEGER_LITERAL:
//             LOG(INFO) << "expr_codegen::EXPR_INTEGER_LITERAL";
//             e->reg = scratch_alloc();
//             AsmLog() << indent(depth) << "mov " << scratch_name(e->reg) << ", " << e->literal_value;
//             break;

//         case EXPR_ADD:
//             LOG(INFO) << "expr_codegen::EXPR_ADD";
//             expr_codegen(depth, e->left);
//             expr_codegen(depth, e->right);
//             AsmLog() << indent(depth) << "add " << scratch_name(e->right->reg) << ", " << scratch_name(e->left->reg);
//             e->reg = e->right->reg;
//             scratch_free(e->left->reg);
//             break;

//         case EXPR_SUBTRACT:
//             LOG(INFO) << "expr_codegen::EXPR_SUBTRACT";
//             expr_codegen(depth, e->left);
//             expr_codegen(depth, e->right);
//             AsmLog() << indent(depth) << "sub " << scratch_name(e->right->reg) << ", " << scratch_name(e->left->reg);
//             e->reg = e->right->reg;
//             scratch_free(e->left->reg);
//             break;

//         case EXPR_MULTIPLY:
//             LOG(INFO) << "expr_codegen::EXPR_MULTIPLY";
//             expr_codegen(depth, e->left);
//             expr_codegen(depth, e->right);
//             AsmLog() << indent(depth) << "imul " << scratch_name(e->right->reg) << ", " << scratch_name(e->left->reg);
//             e->reg = e->right->reg;
//             scratch_free(e->left->reg);
//             break;

//         case EXPR_DIVIDE:
//             LOG(INFO) << "expr_codegen::EXPR_DIVIDE";
//             expr_codegen(depth, e->left);
//             expr_codegen(depth, e->right);
//             AsmLog() << indent(depth) << "mov rax, " << scratch_name(e->left->reg);
//             AsmLog() << indent(depth) << "cqo";
//             AsmLog() << indent(depth) << "idiv " << scratch_name(e->right->reg);
//             AsmLog() << indent(depth) << "mov " << scratch_name(e->left->reg) << ", rax";
//             e->reg = e->left->reg;
//             scratch_free(e->right->reg);
//             break;

//         case EXPR_BOOL_LITERAL:
//             LOG(INFO) << "expr_codegen::EXPR_BOOL_LITERAL";
//             e->reg = scratch_alloc();
//             AsmLog() << indent(depth) << "mov " << scratch_name(e->reg) << ", " << (e->boolean_literal ? 1 : 0);
//             break;

//         case EXPR_ASSIGN:
//             LOG(INFO) << "expr_codegen::EXPR_ASSIGN";
//             expr_codegen(depth, e->right);
//             AsmLog() << indent(depth) << "mov " << symbol_codegen(e->left->symbol) << ", " << scratch_name(e->right->reg);
//             e->reg = e->right->reg;
//             break;

//         case EXPR_CALL:
//         {
//             LOG(INFO) << "expr_codegen::EXPR_CALL";
//             struct expr *arg = nullptr;

//             // Evaluate arguments in reverse order
//             std::vector<int> arg_regs;
//             if (e->right)
//             {
//                 arg = e->right;
//             }

//             while (arg)
//             {
//                 LOG(INFO) << "Analyzing arguments...";
//                 expr_codegen(depth + 1, arg);
//                 arg_regs.push_back(arg->reg);
//                 arg = arg->right;
//             }

//             // Push arguments onto the stack in correct order
//             for (auto it = arg_regs.rbegin(); it != arg_regs.rend(); ++it)
//             {
//                 AsmLog() << indent(depth) << "push " << scratch_name(*it);
//                 scratch_free(*it);
//             }

//             // Call the function
//             expr_codegen(depth + 1, e->left);
//             AsmLog() << indent(depth) << "call " << symbol_codegen(e->left->symbol);

//             // Adjust the stack pointer if there were arguments
//             if (!arg_regs.empty())
//             {
//                 AsmLog() << indent(depth) << "add rsp, " << (arg_regs.size() * 8);
//             }

//             // Allocate register for return value
//             e->reg = scratch_alloc();
//             AsmLog() << indent(depth) << "mov " << scratch_name(e->reg) << ", rax";
//         }
//         break;

//         default:
//             LOG(ERROR) << indent(depth) << "expr_codegen:: Unsupported expression kind: " << expr_to_string(e->kind);
//             exit(EXIT_FAILURE);
//             break;
//     }
// }