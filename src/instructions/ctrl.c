#include "cpu.h"
#include "instructions/instructions.h"

void brk(struct cpu *cpu, uint8_t *, uint8_t *memory) {
	push(cpu, cpu->pc >> 8, memory);
	push(cpu, (cpu->pc & 0xFF) + 1, memory);

	cpu->sr |= SR_B;
	cpu->sr |= SR_I;

	push(cpu, cpu->sp, memory);

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

	uint8_t high, low;
	pull(cpu, &low, memory);
	pull(cpu, &high, memory);
	cpu->pc = high * 0x100 + low;
}

void rts(struct cpu *cpu, uint8_t *, uint8_t *memory) {
	uint8_t high, low;
	pull(cpu, &low, memory);
	pull(cpu, &high, memory);
	cpu->pc = high * 0x100 + low;
}
