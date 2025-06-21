#include <curses.h>

#include "cpu.h"

void init_terminal();

int main() {
    init_terminal();
    struct cpu cpu;
    uint8_t memory[0x10000] = {
        #embed "memory.bin"
    };
    reset(&cpu, memory);
    return run(&cpu, memory);
}

void init_terminal() {
    initscr();
    nodelay(stdscr, true);
    noecho();
    scrollok(stdscr, TRUE);
}
