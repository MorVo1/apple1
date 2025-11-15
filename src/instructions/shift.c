#include "cpu.h"
#include "instructions/instructions.h"

void asl(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (*operand & 0b1000'0000)
		cpu->sr |= SR_C;
	else
		cpu->sr &= ~SR_C;

	*operand = *operand << 1;

	set_n_if_negative(cpu, *operand);
	set_z_if_zero(cpu, *operand);
}

void lsr(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	if (*operand & 0b000'0001)
		cpu->sr |= SR_C;
	else
		cpu->sr &= ~SR_C;

	cpu->sr &= ~SR_N;
	*operand = *operand >> 1;

	set_z_if_zero(cpu, *operand);
}

void rol(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	uint8_t carryin = cpu->sr & SR_C;
	if (*operand & 0b1000'0000)
		cpu->sr |= SR_C;
	else
		cpu->sr &= ~SR_C;

	*operand = *operand << 1;
	*operand |= carryin ? 0b0000'0001 : 0;

	set_n_if_negative(cpu, *operand);
	set_z_if_zero(cpu, *operand);
}

void ror(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	uint8_t carryin = cpu->sr & SR_C;
	if (*operand & 0b0000'0001)
		cpu->sr |= SR_C;
	else
		cpu->sr &= ~SR_C;

	*operand = *operand >> 1;
	*operand |= carryin ? 0b1000'0000 : 0;

	set_n_if_negative(cpu, *operand);
	set_z_if_zero(cpu, *operand);
}
