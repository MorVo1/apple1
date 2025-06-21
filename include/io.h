#include "cpu.h"

#define KBD 0xD010
#define KBDCR 0xD011
#define DSP 0xD012

void handle_keyboard(uint8_t *, uint8_t *);
void handle_display(uint8_t *, uint8_t *, uint8_t);
