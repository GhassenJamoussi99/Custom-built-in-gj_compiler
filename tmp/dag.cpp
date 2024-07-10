#include "dag.h"
#include "expr.h"
#include <map>
#include <vector>
#include <cstring>
#include "decl.h"

std::map<struct expr *, struct dag_node *> expr_to_dag_map;

struct dag_node *expr_to_dag(struct expr *ast) {
    if (!ast) return nullptr;

    // Check if this AST node is already converted to a DAG node
    if (expr_to_dag_map.find(ast) != expr_to_dag_map.end()) {
        return expr_to_dag_map[ast];
    }

    struct dag_node *node = nullptr;
    switch (ast->kind) {
        case EXPR_ADD:
            node = new dag_node(DAG_IADD, expr_to_dag(ast->left), expr_to_dag(ast->right));
            break;
        case EXPR_SUBTRACT:
            node = new dag_node(DAG_IADD, expr_to_dag(ast->left), expr_to_dag(ast->right));
            break;
        case EXPR_MULTIPLY:
            node = new dag_node(DAG_IMUL, expr_to_dag(ast->left), expr_to_dag(ast->right));
            break;
        case EXPR_DIVIDE:
            node = new dag_node(DAG_IMUL, expr_to_dag(ast->left), expr_to_dag(ast->right));
            break;
    }

    // Store the created DAG node in the map
    expr_to_dag_map[ast] = node;
    return node;
}

struct dag_node *ast_to_dag(struct decl *decl_list) {
    if (!decl_list) return nullptr;

    struct dag_node *dag_root = nullptr;
    std::vector<dag_node *> dag_nodes;

    // Traverse the declarations and convert each to a DAG node
    for (struct decl *d = decl_list; d != nullptr; d = d->next) {
        struct dag_node *node = expr_to_dag(d->value);
        dag_nodes.push_back(node);

        // Create an assignment DAG node
        struct dag_node *assign_node = new dag_node(DAG_ASSIGN);
        assign_node->left = new dag_node(d->name, DAG_NAME);
        assign_node->right = node;
        dag_root = assign_node;
    }

    return dag_root;
}
