#include "cpu.h"
#include "instructions/flags.h"

void clc(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->sr &= ~SR_C;
}

void cld(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->sr &= ~SR_D;
}

void cli(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->sr &= ~SR_I;
}

void clv(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->sr &= ~SR_V;
}

void sec(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->sr |= SR_C;
}

void sed(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->sr |= SR_D;
}

void sei(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->sr |= SR_I;
}
