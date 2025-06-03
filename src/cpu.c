#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "instructions/instructions.h"

void reset(struct cpu *cpu, uint8_t *memory) {
    cpu->pc = (memory[0xFFFD] << 8) | memory[0xFFFC];
}

int run(struct cpu *cpu, uint8_t *memory) {
    struct instruction instruction;
    for (;;) {
        instruction = instructions[memory[cpu->pc]];
        if (!instruction.implementation) {
            printf("Unimplemented instruction: %02x\n", memory[cpu->pc]);
            return EXIT_FAILURE;
        }
    }
}
