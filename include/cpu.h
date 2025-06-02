#pragma once

#include <stdint.h>

#define SR_C 1
#define SR_Z (1 << 1)
#define SR_I (1 << 2)
#define SR_D (1 << 3)
#define SR_B (1 << 4)
#define SR_V (1 << 6)
#define SR_N (1 << 7)

#define SIGN_BIT (1 << 7)

struct cpu {
    uint16_t pc;
    uint8_t ac;
    uint8_t x;
    uint8_t y;
    uint8_t sr;
    uint8_t sp;
};

void reset(struct cpu *, uint8_t *);
void run(struct cpu *, uint8_t *);
