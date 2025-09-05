#include "cpu.h"
#include "instructions/instructions.h"

void bcc(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (!(cpu->sr & SR_C))
		cpu->pc += to_signed(*operand);
}

void bcs(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (cpu->sr & SR_C)
		cpu->pc += to_signed(*operand);
}

void beq(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (cpu->sr & SR_Z)
		cpu->pc += to_signed(*operand);
}

void bmi(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (cpu->sr & SR_N)
		cpu->pc += to_signed(*operand);
}

void bne(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (!(cpu->sr & SR_Z))
		cpu->pc += to_signed(*operand);
}

void bpl(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (!(cpu->sr & SR_N))
		cpu->pc += to_signed(*operand);
}

void bvc(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (!(cpu->sr & SR_V))
		cpu->pc += to_signed(*operand);
}

void bvs(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (cpu->sr & SR_V)
		cpu->pc += to_signed(*operand);
}
