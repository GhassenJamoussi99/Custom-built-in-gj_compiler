
#include <iostream>
#include <sstream>
#include <vector>

#include "intel_codegen.h"

#include "expr.h"
#include "stmt.h"
#include "decl.h"
#include "scope.h"
#include "helpers.h"
#include "type.h"

#include "scratch.h"
#include "symbol.h"

#include "asm_log.h"
#include "log.h"

extern std::stringstream dataSection;

static int label_count = 0;

std::string create_label()
{
    return "L" + std::to_string(label_count++);
}

void IntelCodegen::decl_codegen(Decl* d) {
    int depth = 1;

    if (!d) return;

    if (d->decl_symbol->kind == SYMBOL_GLOBAL) {
        if (d->value) {
            dataSection << d->name << ":\n";
            switch (d->value->kind) {
                case EXPR_INTEGER_LITERAL:
                    dataSection << "\t.quad " << d->value->literal_value << "\n";
                    break;
                case EXPR_STRING_LITERAL:
                    dataSection << "\t.string " << d->value->string_literal << "\n";
                    break;
                case EXPR_BOOL_LITERAL:
                    dataSection << "\t.quad " << (d->value->boolean_literal ? 1 : 0) << "\n";
                    break;
                default:
                    std::cerr << "Unsupported initializer for global variable: " << d->name << "\n";
                    exit(1);
            }
        }
    }

    if (d->value && (d->decl_symbol->kind == SYMBOL_LOCAL || d->decl_symbol->kind == SYMBOL_PARAM)) {
        AsmLog() << Helpers::indent(depth + 1) << "# Allocate space for local variable " << d->name;
        switch (d->decl_type->kind) {
            case TYPE_STRING: {
                int reg = Scratch::alloc();
                std::string str_label = create_label();
                std::string init_value = d->value ? d->value->string_literal : "";

                dataSection << str_label << ":\n";
                dataSection << "\t.string " << init_value << "\n";

                AsmLog() << Helpers::indent(depth + 1) << "lea " << Scratch::name(reg) << ", " << str_label;
                AsmLog() << Helpers::indent(depth + 1) << "mov " << IntelCodegen::symbol_codegen(d->decl_symbol) << ", " << Scratch::name(reg) << "\n";
                break;
            }

            case TYPE_BOOLEAN:
            case TYPE_CHARACTER:
            case TYPE_INTEGER: {
                IntelCodegen::expr_codegen(depth + 1, d->value);
                AsmLog() << Helpers::indent(depth + 1) << "mov " << IntelCodegen::symbol_codegen(d->decl_symbol) << ", " << Scratch::name(d->value->reg) << "\n";
                Scratch::free(d->value->reg);
                break;
            }

            default:
                LOG(WARN) << "No type specified";
        }
    }

    if (d->code) {
        AsmLog() << "\n.globl " << d->name;
        AsmLog() << d->name << ":";
        AsmLog() << Helpers::indent(depth + 1) << "push rbp";
        AsmLog() << Helpers::indent(depth + 1) << "mov rbp, rsp";

        int local_variable_count = d->local_var_count;
        int local_variable_size = 8;

        if (local_variable_count <= 1) {
            AsmLog() << Helpers::indent(depth + 1) << "sub rsp, 16";
        } else {
            AsmLog() << Helpers::indent(depth + 1) << "sub rsp, " << local_variable_size * local_variable_count;
        }

        IntelCodegen::stmt_codegen(depth + 1, d->code);
        AsmLog() << Helpers::indent(depth + 1) << "leave";
        AsmLog() << Helpers::indent(depth + 1) << "ret";
    }

    // Recurse to next
    IntelCodegen::decl_codegen(d->next);
}

std::string IntelCodegen::symbol_codegen(Symbol *sym)
{
    std::ostringstream oss;
    switch (sym->kind)
    {
    case SYMBOL_LOCAL:
    case SYMBOL_PARAM:
        if (sym->which >= 0)
            oss << "[rbp + " << sym->which << "]";
        else {
            oss << "[rbp" << sym->which << "]";
        }
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

void IntelCodegen::stmt_codegen(int depth, Stmt *s)
{
    if (!s)
        return;

    switch (s->kind)
    {
    case STMT_EXPR:
        LOG(DEBUG) << "stmt_codegen::Generating code for STMT_EXPR";
        IntelCodegen::expr_codegen(depth, s->expr_value);
        Scratch::free(s->expr_value->reg);
        break;

    case STMT_DECL:
        LOG(DEBUG) << "stmt_codegen::Generating code for STMT_DECL";
        IntelCodegen::decl_codegen(s->decl);
        break;

    case STMT_RETURN:
        LOG(DEBUG) << "stmt_codegen::Generating code for STMT_RETURN";
        IntelCodegen::expr_codegen(depth, s->expr_value);
        AsmLog() << Helpers::indent(depth) << "mov rax, " << Scratch::name(s->expr_value->reg);
        Scratch::free(s->expr_value->reg);
        break;

    case STMT_FOR:
    {
        LOG(DEBUG) << "stmt_codegen::Generating code for STMT_FOR";
        std::string start_label = create_label();
        std::string loop_end_label = create_label();
        
        if (s->init_expr) {
            IntelCodegen::expr_codegen(depth, s->init_expr);
            Scratch::free(s->init_expr->reg);
        }

        AsmLog() << Helpers::indent(depth - 1) << start_label << ":";
        
        if (s->expr_value) {
            IntelCodegen::expr_codegen(depth, s->expr_value);
            AsmLog() << Helpers::indent(depth) << "cmp " << Scratch::name(s->expr_value->reg) << ", 0";
            Scratch::free(s->expr_value->reg);
            AsmLog() << Helpers::indent(depth) << "je " << loop_end_label;
        }

        IntelCodegen::stmt_codegen(depth, s->body);

        if (s->next_expr) {
            IntelCodegen::expr_codegen(depth, s->next_expr);
            Scratch::free(s->next_expr->reg);
        }

        AsmLog() << Helpers::indent(depth) << "jmp " << start_label;
        AsmLog() << Helpers::indent(depth - 1) << loop_end_label << ":";
    }
    break;
    case STMT_IF_ELSE:
    {
        LOG(DEBUG) << "stmt_codegen::Generating code for STMT_IF_ELSE";
        std::string else_label = create_label();
        std::string end_label = create_label();
        IntelCodegen::expr_codegen(depth, s->expr_value);
        AsmLog() << Helpers::indent(depth) << "cmp " << Scratch::name(s->expr_value->reg) << ", 0";
        Scratch::free(s->expr_value->reg);
        AsmLog() << Helpers::indent(depth) << "je " << else_label;
        IntelCodegen::stmt_codegen(depth, s->body);
        AsmLog() << Helpers::indent(depth) << "jmp " << end_label;
        AsmLog() << Helpers::indent(depth - 1) << else_label << ":";
        IntelCodegen::stmt_codegen(depth, s->else_body);
        AsmLog() << Helpers::indent(depth - 1) << end_label << ":";
    }
    break;

    case STMT_WHILE:
    {
        LOG(DEBUG) << "stmt_codegen::Generating code for STMT_WHILE";
        std::string start_label = create_label();
        std::string loop_end_label = create_label();
        AsmLog() << start_label << ":";
        IntelCodegen::expr_codegen(depth, s->expr_value);
        AsmLog() << Helpers::indent(depth) << "cmp " << Scratch::name(s->expr_value->reg) << ", 0";
        Scratch::free(s->expr_value->reg);
        AsmLog() << Helpers::indent(depth) << "je " << loop_end_label;
        IntelCodegen::stmt_codegen(depth, s->body);
        AsmLog() << Helpers::indent(depth) << "jmp " << start_label;
        AsmLog() << Helpers::indent(depth - 1) << loop_end_label << ":";
    }
    break;

    case STMT_BLOCK:
        LOG(DEBUG) << "stmt_codegen::Generating code for STMT_BLOCK";
        IntelCodegen::stmt_codegen(depth, s->body);
        break;

    case STMT_FUNCTION:
        LOG(DEBUG) << "stmt_codegen::Generating code for STMT_FUNCTION";
        IntelCodegen::stmt_codegen(depth, s->body);
        break;

    case STMT_PRINT:
    {
        LOG(DEBUG) << "stmt_codegen::Generating code for STMT_PRINT";

        // Initialize variables
        Expr *curr_arg = s->expr_value;
        int arg_count = 0;
        std::string print_format = "";
        bool lit_vals = false;

        int arg_index = 1; // Start with the second argument register (rsi)

        LOG(DEBUG) << "stmt_codegen::Initializing argument parsing.";

        // Loop through each argument
        while (curr_arg != NULL)
        {
            LOG(DEBUG) << "stmt_codegen::Parsing argument of type: " << curr_arg->left;
            
            if (curr_arg->left->type)
            {
                switch (curr_arg->left->type->kind)
                {
                case TYPE_CHARACTER:
                    print_format += "%c";
                    LOG(DEBUG) << "stmt_codegen::Added format specifier %c.";
                    break;
                case TYPE_INTEGER:
                    print_format += "%d";
                    LOG(DEBUG) << "stmt_codegen::Added format specifier %d.";
                    break;
                case TYPE_STRING:
                    print_format += "%s";
                    LOG(DEBUG) << "stmt_codegen::Added format specifier %s.";
                    break;
                default:
                    print_format += "%s";
                    LOG(DEBUG) << "stmt_codegen::Added format specifier %s.";
                    break;
                }
            } else {
                switch (curr_arg->left->kind)
                {
                case EXPR_CALL:
                {
                    LOG(DEBUG) << "stmt_codegen::EXPR_CALL";
                    switch (curr_arg->left->left->type->subtype->kind)
                    {                
                        case TYPE_CHARACTER:
                            print_format += "%c";
                            LOG(DEBUG) << "stmt_codegen::Added format specifier %c.";
                            break;
                        case TYPE_INTEGER:
                            print_format += "%d";
                            LOG(DEBUG) << "stmt_codegen::Added format specifier %d.";
                            break;
                        case TYPE_STRING:
                            print_format += "%s";
                            LOG(DEBUG) << "stmt_codegen::Added format specifier %s.";
                            break;
                        default:
                            print_format += "%s";
                            LOG(DEBUG) << "stmt_codegen::Added format specifier %s.";
                            break;
                    }                             
                }
                break;
                case EXPR_STRING_LITERAL:
                    lit_vals = true;
                    print_format += curr_arg->left->string_literal;
                    LOG(DEBUG) << "stmt_codegen::Added string literal to format: " << curr_arg->left->string_literal;
                    break;
                case EXPR_BOOL_LITERAL:
                default:
                    LOG(DEBUG) << "stmt_codegen::not a string literal";
                    break;
                }
            }

            curr_arg = curr_arg->right; // Move to the next argument
            arg_count++;
            LOG(DEBUG) << "stmt_codegen::Argument count incremented to: " << arg_count;
        }

        LOG(DEBUG) << "stmt_codegen::Total arguments processed: " << arg_count;

        // Generate a unique label for the format string
        if (lit_vals == false) {
            std::string str_label = create_label();
            LOG(DEBUG) << "stmt_codegen::Generated label for format string: " << str_label;

            // Emit the format string in the .data section
            dataSection << str_label << ":\n";
            dataSection << "\t.string \"" << print_format << "\\n\"\n"; // Note: Added newline and fixed formatting
            LOG(DEBUG) << "stmt_codegen::Format string emitted to data section: " << print_format;

            // Emit the assembly code to load the address of the format string into rdi
            AsmLog() << Helpers::indent(depth) << "lea " << Scratch::argument_registers[0] << ", " << str_label << "";
            LOG(DEBUG) << "stmt_codegen::Loaded format string address into " << Scratch::argument_registers[0];
        }
        

        // Generate code for each argument
        curr_arg = s->expr_value; // Reset to the beginning of arguments
        arg_index = 1;      // Reset argument index for code generation
        IntelCodegen::expr_codegen(depth, curr_arg->left); // Generate code for the argument expression

        LOG(DEBUG) << "stmt_codegen::Starting code generation for arguments.";

        while (curr_arg != NULL && lit_vals == false)
        {
            LOG(DEBUG) << "stmt_codegen::Generated code for argument: " << curr_arg->left->name;

            // Move the argument into the appropriate register
            if (arg_index < Scratch::ARGS_MAX_COUNT)
            {
                AsmLog() << Helpers::indent(depth) << "mov " << Scratch::argument_registers[arg_index] << ", " << Scratch::name(curr_arg->left->reg);
                LOG(DEBUG) << "stmt_codegen::Moved argument to register: " << Scratch::argument_registers[arg_index];
                arg_index++;
            }
            else
            {
                LOG(ERROR) << "stmt_codegen::Too many arguments for printf. Handle overflow.";
                break;
            }

            // Move to the next argument
            curr_arg = curr_arg->right;
        }

        // Emit the call to printf
        AsmLog() << Helpers::indent(depth) << "call printf";
        LOG(DEBUG) << "stmt_codegen::Emitted call to printf.";

        // Free any resources (registers) used for the expressions
        if (s->expr_value->reg)
        {
            LOG(DEBUG) << "stmt_codegen::Freed resources for the expression.";
            Scratch::free(s->expr_value->reg);
        }
        break;
    }

    default:
        LOG(DEBUG) << "stmt_codegen::Unsupported statement kind: " << s->kind << "";
        break;
    }

    IntelCodegen::stmt_codegen(depth, s->next);
}

void IntelCodegen::expr_codegen(int depth, Expr *e)
{
    if (!e)
        return;

    switch (e->kind)
    {
    case EXPR_NAME:
        LOG(INFO) << "expr_codegen::EXPR_NAME";
        LOG(INFO) << "expr_codegen::e->symbol->kind = " << type_to_string(e->symbol->type->kind);
        if (e->symbol->type->kind != TYPE_FUNCTION) {   
            e->reg = Scratch::alloc();
            if ( e->symbol->type->kind == TYPE_STRING && e->symbol->kind == SYMBOL_GLOBAL)
                AsmLog() << Helpers::indent(depth) << "lea " << Scratch::name(e->reg) << ", " << IntelCodegen::symbol_codegen(e->symbol);
            else
                AsmLog() << Helpers::indent(depth) << "mov " << Scratch::name(e->reg) << ", " << IntelCodegen::symbol_codegen(e->symbol);

        }

        break;

    case EXPR_INTEGER_LITERAL:
        LOG(INFO) << "expr_codegen::EXPR_INTEGER_LITERAL";
        e->reg = Scratch::alloc();
        AsmLog() << Helpers::indent(depth) << "mov " << Scratch::name(e->reg) << ", " << e->literal_value;
        break;

    case EXPR_STRING_LITERAL:
    {
        LOG(INFO) << "expr_codegen::EXPR_STRING_LITERAL";
        e->reg = Scratch::alloc();
        // Generate a unique label for the string
        std::string str_label = create_label();

        // Emit the format string in the .data section
        dataSection << str_label << ":\n";
        dataSection << "\t.string " << e->string_literal << "\n"; // Note: Added newline and fixed formatting
        
        // Emit the assembly code to load the address of the format string into rdi
        AsmLog() << Helpers::indent(depth) << "lea " << Scratch::argument_registers[0] << ", " << str_label << "";
        LOG(DEBUG) << "stmt_codegen::Loaded format string address into " << Scratch::argument_registers[0];

        //AsmLog() << Helpers::indent(depth) << "mov " << scratch_name(e->reg) << ", " << str_label;
    }        
    break;

    case EXPR_ADD:
        LOG(INFO) << "expr_codegen::EXPR_ADD";
        IntelCodegen::expr_codegen(depth, e->left);
        IntelCodegen::expr_codegen(depth, e->right);
        AsmLog() << Helpers::indent(depth) << "add " << Scratch::name(e->left->reg) << ", " << Scratch::name(e->right->reg);
        e->reg = e->left->reg;
        Scratch::free(e->right->reg);
        break;

    case EXPR_SUBTRACT:
        LOG(INFO) << "expr_codegen::EXPR_SUBTRACT";
        IntelCodegen::expr_codegen(depth, e->left);
        IntelCodegen::expr_codegen(depth, e->right);
        AsmLog() << Helpers::indent(depth) << "sub " << Scratch::name(e->left->reg) << ", " << Scratch::name(e->right->reg);
        e->reg = e->left->reg;
        Scratch::free(e->left->reg);
        break;

    case EXPR_MULTIPLY:
        LOG(INFO) << "expr_codegen::EXPR_MULTIPLY";
        IntelCodegen::expr_codegen(depth, e->left);
        IntelCodegen::expr_codegen(depth, e->right);
        AsmLog() << Helpers::indent(depth) << "imul " << Scratch::name(e->left->reg) << ", " << Scratch::name(e->right->reg);
        e->reg = e->left->reg;
        Scratch::free(e->right->reg);
        break;

    case EXPR_DIVIDE:
        LOG(INFO) << "expr_codegen::EXPR_DIVIDE";
        IntelCodegen::expr_codegen(depth, e->left);
        IntelCodegen::expr_codegen(depth, e->right);
        AsmLog() << Helpers::indent(depth) << "mov rax, " << Scratch::name(e->left->reg);
        AsmLog() << Helpers::indent(depth) << "cqo";
        AsmLog() << Helpers::indent(depth) << "idiv " << Scratch::name(e->right->reg);
        AsmLog() << Helpers::indent(depth) << "mov " << Scratch::name(e->left->reg) << ", rax";
        e->reg = e->left->reg;
        Scratch::free(e->right->reg);
        break;

    case EXPR_BOOL_LITERAL:
        LOG(INFO) << "expr_codegen::EXPR_BOOL_LITERAL";
        e->reg = Scratch::alloc();
        AsmLog() << Helpers::indent(depth) << "mov " << Scratch::name(e->reg) << ", " << (e->boolean_literal ? 1 : 0);
        break;

    case EXPR_ASSIGN:
        LOG(INFO) << "expr_codegen::EXPR_ASSIGN";
        IntelCodegen::expr_codegen(depth, e->right);
        AsmLog() << Helpers::indent(depth) << "mov " << IntelCodegen::symbol_codegen(e->left->symbol) << ", " << Scratch::name(e->right->reg);
        e->reg = e->right->reg;
        break;
        
    case EXPR_ARG:
        LOG(INFO) << "expr_codegen::EXPR_ARG";
        IntelCodegen::expr_codegen(depth, e->left);
        e->reg = e->left->reg;
        break;

    case EXPR_CALL:
    {
        LOG(INFO) << "expr_codegen::EXPR_CALL";
        Expr *arg = nullptr;

        // Evaluate arguments in reverse order
        std::vector<int> arg_regs;
        if (e->right) {
            arg = e->right;
        }

        while (arg) {
            LOG(INFO) << "Analyzing arguments...";
            IntelCodegen::expr_codegen(depth, arg);
            arg_regs.push_back(arg->reg);
            arg = arg->right;
        }

        // Push arguments onto the stack in correct order
        for (auto it = arg_regs.rbegin(); it != arg_regs.rend(); ++it) {
            AsmLog() << Helpers::indent(depth) << "push " << Scratch::name(*it);
            Scratch::free(*it);
        }

        // Save the result on the stack before calling the function
        AsmLog() << Helpers::indent(depth) << "push rax";

        // Call the function
        IntelCodegen::expr_codegen(depth, e->left);
        AsmLog() << Helpers::indent(depth) << "call " << IntelCodegen::symbol_codegen(e->left->symbol);
        // Move the result of fxnCall to rcx
        e->reg = Scratch::alloc();
        AsmLog() << Helpers::indent(depth) << "mov " << Scratch::name(e->reg) << ", rax";


        AsmLog() << Helpers::indent(depth) << "pop rax";

        // Adjust the stack pointer if there were arguments
        if (!arg_regs.empty()) {
            AsmLog() << Helpers::indent(depth) << "add rsp, " << (arg_regs.size() * 8);
        }

        // Move the result into rax for return
        //AsmLog() << Helpers::indent(depth) << "mov rax, " << scratch_name(e->reg);
    }
    break;
    case EXPR_EQ:
    case EXPR_NEQ:
    case EXPR_LT:
    case EXPR_GT:
    case EXPR_LEQ:
    case EXPR_GEQ:
        LOG(INFO) << "expr_codegen::Comparison";
        IntelCodegen::expr_codegen(depth, e->left);
        IntelCodegen::expr_codegen(depth, e->right);
        AsmLog() << Helpers::indent(depth) << "cmp " << Scratch::name(e->left->reg) << ", " << Scratch::name(e->right->reg);

        switch (e->kind)
        {
        case EXPR_EQ:
            AsmLog() << Helpers::indent(depth) << "sete al";
            break;
        case EXPR_NEQ:
            AsmLog() << Helpers::indent(depth) << "setne al";
            break;
        case EXPR_LT:
            AsmLog() << Helpers::indent(depth) << "setl al";
            break;
        case EXPR_GT:
            AsmLog() << Helpers::indent(depth) << "setg al";
            break;
        case EXPR_LEQ:
            AsmLog() << Helpers::indent(depth) << "setle al";
            break;
        case EXPR_GEQ:
            AsmLog() << Helpers::indent(depth) << "setge al";
            break;
        default:
            LOG(ERROR) << Helpers::indent(depth) << "expr_codegen:: Unsupported comparison kind: " << expr_to_string(e->kind);
            exit(EXIT_FAILURE);
        }

        AsmLog() << Helpers::indent(depth) << "movzx " << Scratch::name(e->left->reg) << ", al";
        e->reg = e->left->reg;
        Scratch::free(e->right->reg);
        break;


    default:
        LOG(ERROR) << Helpers::indent(depth) << "expr_codegen:: Unsupported expression kind: " << expr_to_string(e->kind);
        exit(EXIT_FAILURE);
        break;
    }
}


void IntelCodegen::decl_finish_codegen()
{
    AsmLog() << "\n.data";
    AsmLog() << dataSection.str();
}