#pragma once

typedef enum {
    DAG_ASSIGN,
    DAG_IADD,
    DAG_IMUL,
    DAG_NAME,
    DAG_STRING_VALUE,
    DAG_INTEGER_VALUE
} dag_kind_t;

struct dag_node {
    dag_kind_t kind;
    struct dag_node *left;
    struct dag_node *right;
    std::string name;
    std::string string_value;
    std::string integer_value;

    dag_node(dag_kind_t kind, dag_node* left = nullptr, dag_node* right = nullptr)
        : kind(kind), left(left), right(right) {}

    dag_node(int value)
        : kind(DAG_INTEGER_VALUE), left(nullptr), right(nullptr) {
        integer_value = value;
    }

    dag_node(std::string value, dag_kind_t kind)
        : kind(kind), left(nullptr), right(nullptr) {
        if (kind == DAG_NAME) {
            name = value;
        } else if (kind == DAG_STRING_VALUE) {
            string_value = value;
        }
    }
};

struct dag_node *ast_to_dag(struct decl *ast);
