#ifndef SCRATCH_H
#define SCRATCH_H

#include <iostream>

const int SCRATCH_COUNT = 15;
const int ARGS_MAX_COUNT = 6;

const std::string argument_registers[ARGS_MAX_COUNT] = {
    "rdi", "rsi", "rdx", "rcx", "r8", "r9"
};

const std::string names[SCRATCH_COUNT] = {
    "rax", "rbx", "rcx", "rdx", "rsi", "rdi",
    "r8", "r9", "r10", "r11", "r12", "r13", "r14",
    "r15"
};

int scratch_alloc();
void scratch_free(int r);
std::string scratch_name(int r);

#endif
