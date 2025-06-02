#include "cpu.h"
#include "instructions/instructions.h"

struct instruction instructions[INSTRUCTION_COUNT] = {
    [0xA9] = {lda, OPERAND_IMMEDIATE},
    [0xA5] = {lda, OPERAND_ZEROPAGE},
    [0xB5] = {lda, OPERAND_ZEROPAGE_X},
    [0xAD] = {lda, OPERAND_ABSOLUTE},
    [0xBD] = {lda, OPERAND_ABSOLUTE_X},
    [0xB9] = {lda, OPERAND_ABSOLUTE_Y},
    [0xA1] = {lda, OPERAND_PRE_ZEROPAGE_X},
    [0xB1] = {lda, OPERAND_POST_ZEROPAGE_Y},
    [0xA2] = {ldx, OPERAND_IMMEDIATE},
    [0xA6] = {ldx, OPERAND_ZEROPAGE},
    [0xB6] = {ldx, OPERAND_ZEROPAGE_Y},
    [0xAE] = {ldx, OPERAND_ABSOLUTE},
    [0xBE] = {ldx, OPERAND_ABSOLUTE_Y},
    [0xA0] = {ldy, OPERAND_IMMEDIATE},
    [0xA4] = {ldy, OPERAND_ZEROPAGE},
    [0xB4] = {ldy, OPERAND_ZEROPAGE_X},
    [0xAC] = {ldy, OPERAND_ABSOLUTE},
    [0xBC] = {ldy, OPERAND_ABSOLUTE_X},
    [0x85] = {sta, OPERAND_ZEROPAGE},
    [0x95] = {sta, OPERAND_ZEROPAGE_X},
    [0x8D] = {sta, OPERAND_ABSOLUTE},
    [0x9D] = {sta, OPERAND_ABSOLUTE_X},
    [0x99] = {sta, OPERAND_ABSOLUTE_Y},
    [0x81] = {sta, OPERAND_PRE_ZEROPAGE_X},
    [0x91] = {sta, OPERAND_POST_ZEROPAGE_Y},
    [0x86] = {stx, OPERAND_ZEROPAGE},
    [0x96] = {stx, OPERAND_ZEROPAGE_Y},
    [0x8E] = {stx, OPERAND_ABSOLUTE},
    [0x84] = {sty, OPERAND_ZEROPAGE},
    [0x94] = {sty, OPERAND_ZEROPAGE},
    [0x8C] = {sty, OPERAND_ZEROPAGE},
    [0xAA] = {tax, OPERAND_IMPLIED},
    [0xA8] = {tay, OPERAND_IMPLIED},
    [0xBA] = {tsx, OPERAND_IMPLIED},
    [0x8A] = {txa, OPERAND_IMPLIED},
    [0x9A] = {txs, OPERAND_IMPLIED},
    [0x98] = {tya, OPERAND_IMPLIED}
};

void set_z_if_zero(struct cpu *cpu, uint8_t value) {
    if (!value)
        cpu->sr |= SR_Z;
    else
        cpu->sr &= ~SR_Z;
}

void set_n_if_negative(struct cpu *cpu, uint8_t value) {
    if (value & SIGN_BIT)
        cpu->sr |= SR_N;
    else
        cpu->sr &= ~SR_N;
}

void set_v_on_overflow(struct cpu *cpu, uint8_t a, uint8_t b) {
    if ((a & SIGN_BIT) == (b & SIGN_BIT)) {
        if (a & SIGN_BIT) {
            if ((a + b + (cpu->sr & SR_C ? 1 : 0)) & SIGN_BIT)
                cpu->sr &= ~SR_V;
            else
                cpu->sr |= SR_V;
        }
        else {
            if (!((a + b + (cpu->sr & SR_C ? 1 : 0)) & SIGN_BIT))
                cpu->sr &= ~SR_V;
            else
                cpu->sr |= SR_V;
        }
    }
    else
        cpu->sr &= ~SR_V;
}

void push(struct cpu *cpu, uint8_t value, uint8_t *ram) {
    ram[0x100 + cpu->sp] = value;
    cpu->sp--;
}

void pull(struct cpu *cpu, uint8_t *dest, uint8_t *ram) {
    cpu->sp++;
    *dest = ram[0x100 + cpu->sp];
}
