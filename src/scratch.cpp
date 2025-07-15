#include "scratch.h"
#include <vector>
#include <stdexcept>

const std::string Scratch::argument_registers[Scratch::ARGS_MAX_COUNT] = {
    "rdi", "rsi", "rdx", "rcx", "r8", "r9"
};

const std::string Scratch::names[Scratch::SCRATCH_COUNT] = {
    "rax", "rbx", "rcx", "rdx", "rsi", "rdi",
    "r8", "r9", "r10", "r11", "r12", "r13", "r14",
    "r15"
};

static std::vector<bool> scratch_registers(Scratch::SCRATCH_COUNT, false);

// Allocates a scratch register and returns its index
int Scratch::alloc() {
    for (int i = 0; i < SCRATCH_COUNT; ++i) {
        if (!scratch_registers[i]) {
            scratch_registers[i] = true;
            return i;
        }
    }
    throw std::runtime_error("Out of scratch registers");
}

// Frees the scratch register with the given index
void Scratch::free(int r) {
    if (r < 0 || r >= SCRATCH_COUNT) {
        throw std::invalid_argument("Invalid scratch register index");
    }
    scratch_registers[r] = false;
}

// Returns the name of the scratch register with the given index
std::string Scratch::name(int r) {
    if (r < 0 || r >= SCRATCH_COUNT) {
        throw std::invalid_argument("Invalid scratch register index");
    }
    return names[r];
}
