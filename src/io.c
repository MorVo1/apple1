#include <curses.h>
#include <ctype.h>

#include "cpu.h"
#include "io.h"

uint8_t columns = 0;

void handle_keyboard(uint8_t *operand, uint8_t *memory) {
    char value;
    if (operand - memory == KBDCR) {
        value = getch();
        memory[KBDCR] = (value == ERR) ? 0 : SIGN_BIT;
        memory[KBD] = (value == 10) ? 0x8D : value;
    }
}

void handle_display(uint8_t *operand, uint8_t *memory, uint8_t value) {
    if (operand - memory == DSP) {
        value &= ~SIGN_BIT;

        if (value > '_')
            value -= 32;

        if (isgraph(value) || value == ' ') {
            if (columns == 40) {
                addch('\n');
                columns = 0;
            }
            addch(value);
            columns++;
        } else if (value == '\r') {
            columns = 0;
            addch('\n');
        }

        memory[DSP] = 0;
    }
}
