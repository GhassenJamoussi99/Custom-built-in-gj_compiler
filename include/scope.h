#pragma once

#include "symbol.h"

#define STACK_MAX 256

class Symbol;

class Scope {
public:
    static void enter();
    static void exit();
    static int level();
    static Symbol* lookup(std::string name);
    static void bind(std::string name, Symbol* sym);
};