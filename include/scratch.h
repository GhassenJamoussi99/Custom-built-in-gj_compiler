#ifndef SCRATCH_H
#define SCRATCH_H

#include <iostream>

class Scratch {
public:
    static const int SCRATCH_COUNT = 15;
    static const int ARGS_MAX_COUNT = 6;
    static const std::string argument_registers[ARGS_MAX_COUNT];
    static const std::string names[SCRATCH_COUNT];

    static int alloc();
    static void free(int r);
    static std::string name(int r);
};

#endif
