#include "cpu.h"
#include "instructions/instructions.h"
#include "io.h"

void lda(struct cpu *cpu, uint8_t *operand, uint8_t *memory) {
    handle_keyboard(operand, memory);
    cpu->ac = *operand;
    set_n_if_negative(cpu, cpu->ac);
    set_z_if_zero(cpu, cpu->ac);
}

void ldx(struct cpu *cpu, uint8_t *operand, uint8_t *memory) {
    handle_keyboard(operand, memory);
    cpu->x = *operand;
    set_n_if_negative(cpu, cpu->x);
    set_z_if_zero(cpu, cpu->x);
}

void ldy(struct cpu *cpu, uint8_t *operand, uint8_t *memory) {
    handle_keyboard(operand, memory);
    cpu->y = *operand;
    set_n_if_negative(cpu, cpu->y);
    set_z_if_zero(cpu, cpu->y);
}

void sta(struct cpu *cpu, uint8_t *operand, uint8_t *memory) {
    *operand = cpu->ac;
    handle_display(operand, memory, cpu->ac);
}

void stx(struct cpu *cpu, uint8_t *operand, uint8_t *memory) {
    *operand = cpu->x;
    handle_display(operand, memory, cpu->x);
}

void sty(struct cpu *cpu, uint8_t *operand, uint8_t *memory) {
    *operand = cpu->y;
    handle_display(operand, memory, cpu->y);
}
