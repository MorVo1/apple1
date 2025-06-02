#include "cpu.h"
#include "instructions/instructions.h"

void lda(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    cpu->ac = *operand;
    set_n_if_negative(cpu, cpu->ac);
    set_z_if_zero(cpu, cpu->ac);
}

void ldx(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    cpu->x = *operand;
    set_n_if_negative(cpu, cpu->x);
    set_z_if_zero(cpu, cpu->x);
}

void ldy(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    cpu->y = *operand;
    set_n_if_negative(cpu, cpu->y);
    set_z_if_zero(cpu, cpu->y);
}

void sta(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    *operand = cpu->ac;
}

void stx(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    *operand = cpu->x;
}

void sty(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    *operand = cpu->y;
}
