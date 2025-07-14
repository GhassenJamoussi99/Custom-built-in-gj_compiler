#ifndef DECL_H
#define DECL_H

#include <string>
#include "type.h"
#include "stmt.h"
#include "expr.h"
#include "symbol.h"

// Forward declarations
struct stmt;
struct expr;
struct type;
struct symbol;

class Decl {
public:
    std::string name;
    type* decl_type;
    expr* value;
    stmt* code;
    symbol* decl_symbol;
    Decl* next;
    int local_var_count;

    Decl(const std::string& name, type* type, expr* value, stmt* code, Decl* next);

    void resolve();
    void typecheck(); // If needed, implement later
};

#endif