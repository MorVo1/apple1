#include "cpu.h"
#include "instructions/instructions.h"

void dec(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	(*operand)--;
	set_n_if_negative(cpu, *operand);
	set_z_if_zero(cpu, *operand);
}

void dex(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->x--;
	set_n_if_negative(cpu, cpu->x);
	set_z_if_zero(cpu, cpu->x);
}

void dey(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->y--;
	set_n_if_negative(cpu, cpu->y);
}

void inc(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	(*operand)++;
	set_n_if_negative(cpu, *operand);
	set_z_if_zero(cpu, *operand);
}

void inx(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->x++;
	set_n_if_negative(cpu, cpu->x);
	set_z_if_zero(cpu, cpu->y);
}

void iny(struct cpu *cpu, uint8_t *, uint8_t *) {
	cpu->y++;
	set_n_if_negative(cpu, cpu->y);
	set_z_if_zero(cpu, cpu->y);
}
