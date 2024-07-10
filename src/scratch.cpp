#include "scratch.h"
#include <vector>
#include <stdexcept>

static std::vector<bool> scratch_registers(SCRATCH_COUNT, false);

// Allocates a scratch register and returns its index
int scratch_alloc() {
    for (int i = 0; i < SCRATCH_COUNT; ++i) {
        if (!scratch_registers[i]) {
            scratch_registers[i] = true;
            return i;
        }
    }
    throw std::runtime_error("Out of scratch registers");
}

// Frees the scratch register with the given index
void scratch_free(int r) {
    if (r < 0 || r >= SCRATCH_COUNT) {
        throw std::invalid_argument("Invalid scratch register index");
    }
    scratch_registers[r] = false;
}

// Returns the name of the scratch register with the given index
std::string scratch_name(int r) {
    if (r < 0 || r >= SCRATCH_COUNT) {
        throw std::invalid_argument("Invalid scratch register index");
    }
    return names[r];
}
