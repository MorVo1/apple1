#include <curses.h>
#include <stdbool.h>
#include <string.h>

#include "cpu.h"

void init_terminal();

int main(int argc, char **argv) {
	bool tests = false;
	if (argc == 2 && strcmp(argv[1], "-t") == 0)
		tests = true;

	init_terminal();
	struct cpu cpu;
	uint8_t memory[0x10000];

	if (!tests) {
		uint8_t tmp_memory[0x10000] = {
			#embed "./memory.bin"
		};
		memcpy(memory, tmp_memory, sizeof memory);
		reset(&cpu, memory);
	}
	else {
		uint8_t tmp_memory[0x10000] = {
			#embed "./6502_functional_test.bin"
		};
		memcpy(memory, tmp_memory, sizeof memory);
		cpu.pc = 0x400;
	}	

	return run(&cpu, memory, tests);
}

void init_terminal() {
	initscr();
	nodelay(stdscr, true);
	noecho();
	scrollok(stdscr, true);
}
