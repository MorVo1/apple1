#include "cpu.h"
#include "instructions/instructions.h"

void bcc(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    if (!(cpu->sr & SR_C))
        cpu->pc += *operand;
}

void bcs(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    if (cpu->sr & SR_C)
        cpu->pc += *operand;
}

void beq(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    if (cpu->sr & SR_Z)
        cpu->pc += *operand;
}

void bmi(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    if (cpu->sr & SR_N)
        cpu->pc += *operand;
}

void bne(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    if (!(cpu->sr & SR_Z))
        cpu->pc += *operand;
}

void bpl(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    if (!(cpu->sr & SR_N))
        cpu->pc += *operand;
}

void bvc(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    if (!(cpu->sr & SR_V))
        cpu->pc += *operand;
}

void bvs(struct cpu *cpu, uint8_t *operand, uint8_t *) {
    if (cpu->sr & SR_V)
        cpu->pc += *operand;
}
