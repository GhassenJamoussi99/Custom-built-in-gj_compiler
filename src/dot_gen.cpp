#include <iostream>
#include <fstream>
#include <string>

#include "expr.h"
#include "decl.h"
#include "stmt.h"
#include "param_list.h"
#include "dot_gen.h"
#include "type.h"

#include "log.h"
#include "dot_log.h"


// Global counter to generate unique IDs for nodes
int node_counter = 0;

// Helper function to generate unique node labels
std::string generate_node_label(const std::string& base, int id) {
    return base + "_" + std::to_string(id);
}

void print_expr_dot(struct expr* e) {
    if (!e) return;

    std::string node_label = generate_node_label("EXPR", node_counter++);
    std::string expr_label = expr_to_string(e->kind);  // Get string representation of the expression kind

    if (e->kind == EXPR_INTEGER_LITERAL || e->kind == EXPR_CHAR_LITERAL || e->kind == EXPR_BOOL_LITERAL || e->kind == EXPR_STRING_LITERAL) {
        // It's a literal value
        std::string value = "";
        if (e->kind == EXPR_INTEGER_LITERAL) {
            value = std::to_string(e->literal_value);
        } else if (e->kind == EXPR_CHAR_LITERAL) {
            value = std::string(1, e->char_literal);
        } else if (e->kind == EXPR_BOOL_LITERAL) {
            value = e->boolean_literal ? "true" : "false";
        } else if (e->kind == EXPR_STRING_LITERAL) {
            // Escape double quotes in the string literal
            std::string escaped_value;
            for (char c : e->string_literal) {
                if (c == '"') {
                    escaped_value += "\\\"";
                } else {
                    escaped_value += c;
                }
            }
            value = escaped_value;
        }
        DotLog() << node_label << " [label=\"{" << expr_label << " | { " << value << " }}\"];\n";
    } else if (e->kind == EXPR_NAME) {
        DotLog() << node_label << " [label=\"{" << expr_label << " | { " << e->name << " }}\"];\n";
    } else if (e->kind == EXPR_EQ || e->kind == EXPR_NEQ || e->kind == EXPR_LT ||
               e->kind == EXPR_GT || e->kind == EXPR_LEQ || e->kind == EXPR_GEQ) {
        // Handle binary operators
        DotLog() << node_label << " [label=\"{" << expr_label << " | { <left> left | <right> right }}\"];\n";

        if (e->left) {
            std::string left_label = generate_node_label("EXPR", node_counter);
            print_expr_dot(e->left);
            DotLog() << node_label << ":left -> " << left_label << ";\n";
        }
        if (e->right) {
            std::string right_label = generate_node_label("EXPR", node_counter);
            print_expr_dot(e->right);
            DotLog() << node_label << ":right -> " << right_label << ";\n";
        }
    } else {
        // Handle other non-literal values
        DotLog() << node_label << " [label=\"{" << expr_label << " | { <left> left | <right> right }}\"];\n";

        if (e->left) {
            std::string left_label = generate_node_label("EXPR", node_counter);
            print_expr_dot(e->left);
            DotLog() << node_label << ":left -> " << left_label << ";\n";
        }
        if (e->right) {
            std::string right_label = generate_node_label("EXPR", node_counter);
            print_expr_dot(e->right);
            DotLog() << node_label << ":right -> " << right_label << ";\n";
        }
    }
}


void print_stmt_dot(Stmt* s) {
    if (!s) return;

    std::string node_label = generate_node_label("STMT", node_counter++);
    std::string stmt_label = Stmt::to_string(s->kind);  // Modify as needed to distinguish statement types
    DotLog() << node_label << " [label=\"{" << stmt_label << " | { <decl> decl | <init_expr> init_expr | <expr> expr | <next_expr> next_expr | <body> body | <else_body> else_body | <next> next }}\"];\n";

    if (s->decl) {
        std::string decl_label = generate_node_label("DECL", node_counter);
        print_decl_list_dot(s->decl);
        DotLog() << node_label << ":decl -> " << decl_label << ";\n";
    }
    if (s->init_expr) {
        std::string init_expr_label = generate_node_label("EXPR", node_counter);
        print_expr_dot(s->init_expr);
        DotLog() << node_label << ":init_expr -> " << init_expr_label << ";\n";
    }
    if (s->expr_value) {
        std::string expr_label = generate_node_label("EXPR", node_counter);
        print_expr_dot(s->expr_value);
        DotLog() << node_label << ":expr -> " << expr_label << ";\n";
    }
    if (s->next_expr) {
        std::string next_expr_label = generate_node_label("EXPR", node_counter);
        print_expr_dot(s->next_expr);
        DotLog() << node_label << ":next_expr -> " << next_expr_label << ";\n";
    }
    if (s->body) {
        std::string body_label = generate_node_label("STMT", node_counter);
        print_stmt_dot(s->body);
        DotLog() << node_label << ":body -> " << body_label << ";\n";
    }
    if (s->else_body) {
        std::string else_body_label = generate_node_label("STMT", node_counter);
        print_stmt_dot(s->else_body);
        DotLog() << node_label << ":else_body -> " << else_body_label << ";\n";
    }
    if (s->next) {
        std::string next_label = generate_node_label("STMT", node_counter);
        print_stmt_dot(s->next);
        DotLog() << node_label << ":next -> " << next_label << ";\n";
    }
}

void print_param_list_dot(struct param_list* params) {
    if (!params) return;

    std::string node_label = generate_node_label("PARAM", node_counter++);
    DotLog() << node_label << " [label=\"{PARAM | { <name> name | <type> type | <next> next }}\"];\n";

    if (params->type) {
        std::string type_label = generate_node_label("TYPE", node_counter);
        print_type_dot(params->type);
        DotLog() << node_label << ":type -> " << type_label << ";\n";
    }

    if (params->next) {
        std::string next_label = generate_node_label("PARAM", node_counter);
        print_param_list_dot(params->next);
        DotLog() << node_label << ":next -> " << next_label << ";\n";
    }
}

void print_type_dot(Type* t) {
    if (!t) return;

    std::string node_label = generate_node_label("SUBTYPE", node_counter++);
    DotLog() << node_label << " [label=\"{" << type_to_string(t->kind) << " | { <subtype> subtype | <params> params }}\"];\n";

    if (t->subtype) {
        std::string subtype_label = generate_node_label("TYPE", node_counter);
        print_type_dot(t->subtype);
        DotLog() << node_label << ":subtype -> " << subtype_label << ";\n";
    }

    if (t->params) {
        std::string params_label = generate_node_label("PARAM", node_counter);
        print_param_list_dot(t->params);
        DotLog() << node_label << ":params -> " << params_label << ";\n";
    }
}



void print_decl_list_dot(Decl* decl_list) {
    Decl* current = decl_list;

    while (current) {
        std::string node_label = generate_node_label("DECL", node_counter++);
        DotLog() << node_label << " [label=\"{DECL_" << current->name 
                 << " | { <type> type | <value> value | <code> code | <next> next }}\"];\n";

        if (current->decl_type) {
            std::string type_label = generate_node_label("TYPE", node_counter);
            DotLog() << type_label << " [label=\"{" << type_to_string(current->decl_type->kind)
                     << "| { <subtype> subtype | <params> params}}\"];\n";

            if (current->decl_type->subtype) {
                std::string subtype_label = generate_node_label("SUBTYPE", node_counter);
                print_type_dot(current->decl_type->subtype);
                DotLog() << type_label << ":subtype -> " << subtype_label << ";\n";
            }

            if (current->decl_type->params) {
                std::string params_label = generate_node_label("PARAM", node_counter);
                print_param_list_dot(current->decl_type->params);
                DotLog() << type_label << ":params -> " << params_label << ";\n";
            }

            DotLog() << node_label << ":type -> " << type_label << ";\n";
        }

        if (current->value) {
            std::string value_label = generate_node_label("EXPR", node_counter);
            print_expr_dot(current->value);
            DotLog() << node_label << ":value -> " << value_label << ";\n";
        }

        if (current->code) {
            std::string code_label = generate_node_label("STMT", node_counter);
            print_stmt_dot(current->code);
            DotLog() << node_label << ":code -> " << code_label << ";\n";
        }

        if (current->next) {
            std::string next_label = generate_node_label("DECL", node_counter);
            DotLog() << node_label << ":next -> " << next_label << ";\n";
        }

        current = current->next;
    }
}