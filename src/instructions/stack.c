#include "cpu.h"
#include "instructions/instructions.h"

void pha(struct cpu *cpu, uint8_t *, uint8_t *ram) {
    push(cpu, cpu->ac, ram);
}

void php(struct cpu *cpu, uint8_t *, uint8_t *ram) {
    push(cpu, cpu->sr, ram);
}

void pla(struct cpu *cpu, uint8_t *, uint8_t *ram) {
    pull(cpu, &cpu->ac, ram);
    set_n_if_negative(cpu, cpu->ac);
    set_z_if_zero(cpu, cpu->ac);
}

void plp(struct cpu *cpu, uint8_t *, uint8_t *ram) {
    pull(cpu, &cpu->sr, ram);
}
