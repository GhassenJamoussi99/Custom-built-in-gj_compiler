#ifndef DECL_H
#define DECL_H

#include <string>
#include "expr.h"

// Forward declarations
class Stmt;
class Expr;
class Type;
class Symbol;

class Decl {
public:
    std::string name;
    Type* decl_type;
    Expr* value;
    Stmt* code;
    Symbol* decl_symbol;
    Decl* next;
    int local_var_count;

    Decl(const std::string& name, Type* type, Expr* value, Stmt* code, Decl* next);

    void resolve();
    void typecheck(); // If needed, implement later
};

#endif