#include "cpu.h"
#include "instructions/instructions.h"

void brk(struct cpu *cpu, uint8_t *, uint8_t *ram) {
    push(cpu, cpu->pc >> 8, ram);
    push(cpu, (cpu->pc & 0xFF) + 1, ram);

    cpu->sr |= SR_B;
    cpu->sr |= SR_I;
    
    push(cpu, cpu->sp, ram);

    // I am subtracting 1 from it because it gets added later on in my main loop.
    cpu->pc = ram[0xFFFE] + ram[0xFFFF] * 0x100 - 1;
}

void jmp(struct cpu *cpu, uint8_t *operand, uint8_t *ram) {
    // I am subtracting 1 from it because it gets added later on in my main loop.
    cpu->pc = operand - ram - 1;
}

void jsr(struct cpu *cpu, uint8_t *operand, uint8_t *ram) {
    push(cpu, cpu->pc >> 8, ram);
    push(cpu, cpu->pc & 0xFF, ram);

    // I am subtracting 1 from it because it gets added later on in my main loop.
    cpu->pc = operand - ram - 1;
}

void rti(struct cpu *cpu, uint8_t *, uint8_t *ram) {
    pull(cpu, &cpu->sr, ram);
    
    uint8_t high, low;
    pull(cpu, &low, ram);
    pull(cpu, &high, ram);
    cpu->pc = high * 0x100 + low;
}

void rts(struct cpu *cpu, uint8_t *, uint8_t *ram) {
    uint8_t high, low;
    pull(cpu, &low, ram);
    pull(cpu, &high, ram);
    cpu->pc = high * 0x100 + low;
}
