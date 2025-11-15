#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "instructions/instructions.h"

void reset(struct cpu *cpu, uint8_t *memory) {
	cpu->pc = (memory[0xFFFD] << 8) | memory[0xFFFC];
}

int run(struct cpu *cpu, uint8_t *memory, bool tests) {
	struct instruction instruction;
	uint16_t operand;
	FILE *logfile = nullptr;

	if (tests)
		logfile = fopen("log.txt", "w");

	for (;;) {
		instruction = instructions[memory[cpu->pc]];
		if (!instruction.implementation) {
			printf("Unimplemented instruction: %02x at %04x\n", memory[cpu->pc], cpu->pc);
			return EXIT_FAILURE;
		}
		
		log_if_tests(tests, &instruction, cpu, memory, logfile);

		switch (instruction.address_mode) {
			case OPERAND_ACCUMULATOR:
				instruction.implementation(cpu, &cpu->ac, memory);
				break;
			case OPERAND_ABSOLUTE:
				operand = memory[++cpu->pc];
				operand |= memory[++cpu->pc] << 8;
				instruction.implementation(cpu, &memory[operand], memory);
				break;
			case OPERAND_ABSOLUTE_X:
				operand = memory[++cpu->pc];
				operand |= memory[++cpu->pc] << 8;
				operand += cpu->x;
				instruction.implementation(cpu, &memory[operand], memory);
				break;
			case OPERAND_ABSOLUTE_Y:
				operand = memory[++cpu->pc];
				operand |= memory[++cpu->pc] << 8;
				operand += cpu->y;
				instruction.implementation(cpu, &memory[operand], memory);
				break;
			case OPERAND_IMMEDIATE:
				instruction.implementation(cpu, &memory[++cpu->pc], memory);
				break;
			case OPERAND_IMPLIED:
				instruction.implementation(cpu, nullptr, memory);
				break;
			case OPERAND_ZEROPAGE:
				operand = memory[++cpu->pc];
				instruction.implementation(cpu, &memory[operand], memory);
				break;
			case OPERAND_ZEROPAGE_X:
				operand = memory[++cpu->pc] + cpu->x;
				operand &= 0xFF;
				instruction.implementation(cpu, &memory[operand], memory);
				break;
			case OPERAND_ZEROPAGE_Y:
				operand = memory[++cpu->pc] + cpu->y;
				operand &= 0xFF;
				instruction.implementation(cpu, &memory[operand], memory);
				break;
			case OPERAND_PRE_ZEROPAGE_X:
				operand = memory[++cpu->pc] + cpu->x;
				operand &= 0xFF;
				operand = memory[operand + 1] << 8 | memory[operand];
				instruction.implementation(cpu, &memory[operand], memory);
				break;
			case OPERAND_POST_ZEROPAGE_Y:
				operand = memory[++cpu->pc];
				operand = memory[operand + 1] << 8 | memory[operand];
				operand += cpu->y;
				instruction.implementation(cpu, &memory[operand], memory);
				break;
			case OPERAND_INDIRECT:
				operand = memory[++cpu->pc];
				operand |= memory[++cpu->pc] << 8;
				operand = memory[operand + 1] << 8 | memory[operand];
				instruction.implementation(cpu, &memory[operand], memory);
				break;
			case OPERAND_RELATIVE:
				operand = ++cpu->pc;
				instruction.implementation(cpu, &memory[operand], memory);
		}
		cpu->pc++;
		refresh();
	}
}

void log_if_tests(bool tests, struct instruction *instruction, struct cpu *cpu, uint8_t *memory, FILE *logfile) {
	if (!tests)
		return;

	fprintf(logfile, "PC = %04x AC = %02x X = %02x Y = %02x SP = %02x SR = %08b\n", cpu->pc, cpu->ac, cpu->x, cpu->y, cpu->sp, cpu->sr);

	switch (instruction->address_mode) {
		case OPERAND_ACCUMULATOR:
		case OPERAND_IMPLIED:
			fprintf(logfile, "%02x\n\n", memory[cpu->pc]);
			break;
		case OPERAND_ABSOLUTE:
		case OPERAND_ABSOLUTE_X:
		case OPERAND_ABSOLUTE_Y:
		case OPERAND_INDIRECT:
			fprintf(logfile, "%02x %04x\n\n", memory[cpu->pc], memory[cpu->pc + 1] + (memory[cpu->pc + 2] << 8));
			break;	
		case OPERAND_IMMEDIATE:
		case OPERAND_ZEROPAGE:
		case OPERAND_ZEROPAGE_X:
		case OPERAND_ZEROPAGE_Y:
		case OPERAND_PRE_ZEROPAGE_X:
		case OPERAND_POST_ZEROPAGE_Y:
		case OPERAND_RELATIVE:
			fprintf(logfile, "%02x %02x\n\n", memory[cpu->pc], memory[cpu->pc + 1]);
	}

}

