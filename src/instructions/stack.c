#include "cpu.h"
#include "instructions/instructions.h"

void pha(struct cpu *cpu, uint8_t *, uint8_t *memory) {
    push(cpu, cpu->ac, memory);
}

void php(struct cpu *cpu, uint8_t *, uint8_t *memory) {
    push(cpu, cpu->sr, memory);
}

void pla(struct cpu *cpu, uint8_t *, uint8_t *memory) {
    pull(cpu, &cpu->ac, memory);
    set_n_if_negative(cpu, cpu->ac);
    set_z_if_zero(cpu, cpu->ac);
}

void plp(struct cpu *cpu, uint8_t *, uint8_t *memory) {
    pull(cpu, &cpu->sr, memory);
}
