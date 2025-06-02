#include "cpu.h"

int main() {
    struct cpu cpu;
    uint8_t memory[0x10000];
    reset(&cpu, memory);
    run(&cpu, memory);
}
