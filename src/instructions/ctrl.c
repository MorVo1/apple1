#include "cpu.h"
#include "instructions/instructions.h"

void brk(struct cpu *cpu, uint8_t *, uint8_t *memory) {
	uint16_t ret = cpu->pc + 2;
	push(cpu, ret >> 8, memory);
	push(cpu, ret & 0xFF, memory);

	push(cpu, cpu->sr | SR_PHP_SET, memory);
	cpu->sr |= SR_I;

	// I am subtracting 1 from it because it gets added later on in my main loop.
	cpu->pc = memory[0xFFFE] + memory[0xFFFF] * 0x100 - 1;
}

void jmp(struct cpu *cpu, uint8_t *operand, uint8_t *memory) {
	// I am subtracting 1 from it because it gets added later on in my main loop.
	cpu->pc = operand - memory - 1;
}

void jsr(struct cpu *cpu, uint8_t *operand, uint8_t *memory) {
	push(cpu, cpu->pc >> 8, memory);
	push(cpu, cpu->pc & 0xFF, memory);

	// I am subtracting 1 from it because it gets added later on in my main loop.
	cpu->pc = operand - memory - 1;
}

void rti(struct cpu *cpu, uint8_t *, uint8_t *memory) {
	pull(cpu, &cpu->sr, memory);
	cpu->sr &= ~SR_PLP_IGNORED;

	uint8_t high, low;
	pull(cpu, &low, memory);
	pull(cpu, &high, memory);
	cpu->pc = high << 8 | low;

	// I am subtracting 1 from it because it gets added later on in my main loop.
	cpu->pc -= 1;
}

void rts(struct cpu *cpu, uint8_t *, uint8_t *memory) {
	uint8_t high, low;
	pull(cpu, &low, memory);
	pull(cpu, &high, memory);
	cpu->pc = high << 8 | low;
}
