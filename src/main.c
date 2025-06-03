#include "cpu.h"

int main() {
    struct cpu cpu;
    uint8_t memory[0x10000] = {
        #embed "memory.bin"
    };
    reset(&cpu, memory);
    return run(&cpu, memory);
}
