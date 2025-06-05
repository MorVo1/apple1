#pragma once

#include <stdint.h>

#include "cpu.h"

#include "instructions/load.h"
#include "instructions/trans.h"
#include "instructions/stack.h"
#include "instructions/shift.h"
#include "instructions/logic.h"
#include "instructions/arith.h"
#include "instructions/inc.h"
#include "instructions/ctrl.h"
#include "instructions/bra.h"
#include "instructions/flags.h"
#include "instructions/nop.h"

#define INSTRUCTION_COUNT 0x100

enum address_mode {
    OPERAND_ACCUMULATOR,
	OPERAND_ABSOLUTE,
	OPERAND_ABSOLUTE_X,
	OPERAND_ABSOLUTE_Y,
	OPERAND_IMMEDIATE,
	OPERAND_IMPLIED,
	OPERAND_ZEROPAGE,
	OPERAND_ZEROPAGE_X,
	OPERAND_ZEROPAGE_Y,
	OPERAND_PRE_ZEROPAGE_X,
	OPERAND_POST_ZEROPAGE_Y,
	OPERAND_INDIRECT,
	OPERAND_RELATIVE
};

struct instruction {
    void (*implementation)(struct cpu *, uint8_t *, uint8_t *);
    enum address_mode address_mode;
};

extern struct instruction instructions[INSTRUCTION_COUNT];

// The functions below do not represent the 6502's instructions

void set_z_if_zero(struct cpu *, uint8_t);
void set_n_if_negative(struct cpu *, uint8_t);
void set_v_on_overflow(struct cpu *, uint8_t, uint8_t);
void push(struct cpu *, uint8_t, uint8_t *);
void pull(struct cpu *, uint8_t *, uint8_t *);

[[maybe_unused]] static int8_t to_signed(uint8_t value) {
    if (value > INT8_MAX)
        return value - 256;
    return value;
}
