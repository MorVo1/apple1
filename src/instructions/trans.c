#include "cpu.h"
#include "instructions/instructions.h"

void tax(struct cpu *cpu, uint8_t *, uint8_t *) {
    cpu->x = cpu->ac;
    set_n_if_negative(cpu, cpu->x);
    set_z_if_zero(cpu, cpu->x);
}

void tay(struct cpu *cpu, uint8_t *, uint8_t *) {
    cpu->y = cpu->ac;
    set_n_if_negative(cpu, cpu->y);
    set_z_if_zero(cpu, cpu->y);
}

void tsx(struct cpu *cpu, uint8_t *, uint8_t *) {
    cpu->x = cpu->sp;
    set_n_if_negative(cpu, cpu->x);
    set_z_if_zero(cpu, cpu->x);
}

void txa(struct cpu *cpu, uint8_t *, uint8_t *) {
    cpu->ac = cpu->x;
    set_n_if_negative(cpu, cpu->ac);
    set_z_if_zero(cpu, cpu->ac);
}

void txs(struct cpu *cpu, uint8_t *, uint8_t *) {
    cpu->sp = cpu->x;
}

void tya(struct cpu *cpu, uint8_t *, uint8_t *) {
    cpu->ac = cpu->y;
    set_n_if_negative(cpu, cpu->ac);
    set_z_if_zero(cpu, cpu->ac);
}
