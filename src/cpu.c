#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "instructions/instructions.h"

void reset(struct cpu *cpu, uint8_t *memory) {
    cpu->pc = (memory[0xFFFD] << 8) | memory[0xFFFC];
}

int run(struct cpu *cpu, uint8_t *memory) {
    struct instruction instruction;
    uint16_t operand;

    for (;;) {
        instruction = instructions[memory[cpu->pc]];
        if (!instruction.implementation) {
            printf("Unimplemented instruction: %02x\n", memory[cpu->pc]);
            return EXIT_FAILURE;
        }

        switch (instruction.address_mode) {
            case OPERAND_ACCUMULATOR:
                instruction.implementation(cpu, &cpu->ac, memory);
                break;
            case OPERAND_ABSOLUTE:
                operand = memory[++cpu->pc] | memory[++cpu->pc] << 8;
                instruction.implementation(cpu, &memory[operand], memory);
                break;
            case OPERAND_ABSOLUTE_X:
                operand = memory[++cpu->pc] | memory[++cpu->pc] << 8;
                operand += cpu->x;
                instruction.implementation(cpu, &memory[operand], memory);
                break;
            case OPERAND_ABSOLUTE_Y:
                operand = memory[++cpu->pc] | memory[++cpu->pc] << 8;
                operand += cpu->y;
                instruction.implementation(cpu, &memory[operand], memory);
                break;
            case OPERAND_IMMEDIATE:
                instruction.implementation(cpu, &memory[++cpu->pc], memory);
                break;
            case OPERAND_IMPLIED:
                instruction.implementation(cpu, nullptr, memory);
                break;
            case OPERAND_ZEROPAGE:
                operand = memory[++cpu->pc];
                instruction.implementation(cpu, &memory[operand], memory);
                break;
            case OPERAND_ZEROPAGE_X:
                operand = memory[++cpu->pc] + cpu->x;
                instruction.implementation(cpu, &memory[operand], memory);
                break;
            case OPERAND_ZEROPAGE_Y:
                operand = memory[++cpu->pc] + cpu->y;
                instruction.implementation(cpu, &memory[operand], memory);
                break;
            case OPERAND_PRE_ZEROPAGE_X:
                operand = memory[++cpu->pc] + cpu->x;
                operand = memory[operand + 1] << 8 | memory[operand];
                instruction.implementation(cpu, &memory[operand], memory);
                break;
            case OPERAND_POST_ZEROPAGE_Y:
                operand = memory[++cpu->pc];
                operand = memory[operand + 1] << 8 | memory[operand];
                operand += cpu->y;
                instruction.implementation(cpu, &memory[operand], memory);
            case OPERAND_INDIRECT:
                operand = memory[++cpu->pc] | memory[++cpu->pc] << 8;
                operand = memory[operand + 1] << 8 | memory[operand];
                instruction.implementation(cpu, &memory[operand], memory);
                break;
            case OPERAND_RELATIVE:
                operand = ++cpu->pc;
                instruction.implementation(cpu, &memory[operand], memory);
        }
        cpu->pc++;
    }
}
