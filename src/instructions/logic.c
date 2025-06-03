#include "cpu.h"
#include "instructions/instructions.h"

void and(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    cpu->ac &= *operand;
    set_n_if_negative(cpu, cpu->ac);
    set_z_if_zero(cpu, cpu->ac);
}

void bit(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    uint8_t result = cpu->ac & *operand;
    set_n_if_negative(cpu, *operand);
    set_z_if_zero(cpu, result);

    if (*operand & SR_V)
        cpu->sr |= SR_V;
    else
        cpu->sr &= ~SR_V;

}

void eor(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    cpu->ac ^= *operand;
    set_n_if_negative(cpu, cpu->ac);
    set_z_if_zero(cpu, cpu->ac);
}

void ora(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    cpu->ac |= *operand;
    set_n_if_negative(cpu, cpu->ac);
    set_z_if_zero(cpu, cpu->ac);
}
