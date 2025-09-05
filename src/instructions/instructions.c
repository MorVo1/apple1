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
	[0x94] = {sty, OPERAND_ZEROPAGE_X},
	[0x8C] = {sty, OPERAND_ABSOLUTE},
	[0xAA] = {tax, OPERAND_IMPLIED},
	[0xA8] = {tay, OPERAND_IMPLIED},
	[0xBA] = {tsx, OPERAND_IMPLIED},
	[0x8A] = {txa, OPERAND_IMPLIED},
	[0x9A] = {txs, OPERAND_IMPLIED},
	[0x98] = {tya, OPERAND_IMPLIED},
	[0x48] = {pha, OPERAND_IMPLIED},
	[0x08] = {php, OPERAND_IMPLIED},
	[0x68] = {pla, OPERAND_IMPLIED},
	[0x28] = {plp, OPERAND_IMPLIED},
	[0x0A] = {asl, OPERAND_ACCUMULATOR},
	[0x06] = {asl, OPERAND_ZEROPAGE},
	[0x16] = {asl, OPERAND_ZEROPAGE_X},
	[0x0E] = {asl, OPERAND_ABSOLUTE},
	[0x1E] = {asl, OPERAND_ABSOLUTE_X},
	[0x4A] = {lsr, OPERAND_ACCUMULATOR},
	[0x46] = {lsr, OPERAND_ZEROPAGE},
	[0x56] = {lsr, OPERAND_ZEROPAGE_X},
	[0x4E] = {lsr, OPERAND_ABSOLUTE},
	[0x5E] = {lsr, OPERAND_ABSOLUTE_X},
	[0x2A] = {rol, OPERAND_ACCUMULATOR},
	[0x26] = {rol, OPERAND_ZEROPAGE},
	[0x36] = {rol, OPERAND_ZEROPAGE_X},
	[0x2E] = {rol, OPERAND_ABSOLUTE},
	[0x3E] = {rol, OPERAND_ABSOLUTE_X},
	[0x6A] = {ror, OPERAND_ACCUMULATOR},
	[0x66] = {ror, OPERAND_ZEROPAGE},
	[0x76] = {ror, OPERAND_ZEROPAGE_X},
	[0x6E] = {ror, OPERAND_ABSOLUTE},
	[0x7E] = {ror, OPERAND_ABSOLUTE_X},
	[0x29] = {and, OPERAND_IMMEDIATE},
	[0x25] = {and, OPERAND_ZEROPAGE},
	[0x35] = {and, OPERAND_ZEROPAGE_X},
	[0x2D] = {and, OPERAND_ABSOLUTE},
	[0x3D] = {and, OPERAND_ABSOLUTE_X},
	[0x39] = {and, OPERAND_ABSOLUTE_Y},
	[0x21] = {and, OPERAND_PRE_ZEROPAGE_X},
	[0x31] = {and, OPERAND_POST_ZEROPAGE_Y},
	[0x2C] = {bit, OPERAND_ABSOLUTE},
	[0x24] = {bit, OPERAND_ZEROPAGE},
	[0x49] = {eor, OPERAND_IMMEDIATE},
	[0x45] = {eor, OPERAND_ZEROPAGE},
	[0x55] = {eor, OPERAND_ZEROPAGE_X},
	[0x4D] = {eor, OPERAND_ABSOLUTE},
	[0x5D] = {eor, OPERAND_ABSOLUTE_X},
	[0x59] = {eor, OPERAND_ABSOLUTE_Y},
	[0x41] = {eor, OPERAND_PRE_ZEROPAGE_X},
	[0x51] = {eor, OPERAND_POST_ZEROPAGE_Y},
	[0x09] = {ora, OPERAND_IMMEDIATE},
	[0x05] = {ora, OPERAND_ZEROPAGE},
	[0x15] = {ora, OPERAND_ZEROPAGE_X},
	[0x0D] = {ora, OPERAND_ABSOLUTE},
	[0x1D] = {ora, OPERAND_ABSOLUTE_X},
	[0x19] = {ora, OPERAND_ABSOLUTE_Y},
	[0x01] = {ora, OPERAND_PRE_ZEROPAGE_X},
	[0x11] = {ora, OPERAND_POST_ZEROPAGE_Y},
	[0x69] = {adc, OPERAND_IMMEDIATE},
	[0x65] = {adc, OPERAND_ZEROPAGE},
	[0x75] = {adc, OPERAND_ZEROPAGE_X},
	[0x6D] = {adc, OPERAND_ABSOLUTE},
	[0x7D] = {adc, OPERAND_ABSOLUTE_X},
	[0x79] = {adc, OPERAND_ABSOLUTE_Y},
	[0x61] = {adc, OPERAND_PRE_ZEROPAGE_X},
	[0x71] = {adc, OPERAND_POST_ZEROPAGE_Y},
	[0xC9] = {cmp, OPERAND_IMMEDIATE},
	[0xC5] = {cmp, OPERAND_ZEROPAGE},
	[0xD5] = {cmp, OPERAND_ZEROPAGE_X},
	[0xCD] = {cmp, OPERAND_ABSOLUTE},
	[0xDD] = {cmp, OPERAND_ABSOLUTE_X},
	[0xD9] = {cmp, OPERAND_ABSOLUTE_Y},
	[0xC1] = {cmp, OPERAND_PRE_ZEROPAGE_X},
	[0xD1] = {cmp, OPERAND_POST_ZEROPAGE_Y},
	[0xE0] = {cpx, OPERAND_IMMEDIATE},
	[0xEC] = {cpx, OPERAND_ABSOLUTE},
	[0xE4] = {cpx, OPERAND_ZEROPAGE},
	[0xC0] = {cpy, OPERAND_IMMEDIATE},
	[0xCC] = {cpy, OPERAND_ZEROPAGE},
	[0xC4] = {cpy, OPERAND_ZEROPAGE},
	[0xE9] = {sbc, OPERAND_IMMEDIATE},
	[0xE5] = {sbc, OPERAND_ZEROPAGE},
	[0xF5] = {sbc, OPERAND_ZEROPAGE_X},
	[0xED] = {sbc, OPERAND_ABSOLUTE},
	[0xFD] = {sbc, OPERAND_ABSOLUTE_X},
	[0xF9] = {sbc, OPERAND_ABSOLUTE_Y},
	[0xE1] = {sbc, OPERAND_PRE_ZEROPAGE_X},
	[0xF1] = {sbc, OPERAND_POST_ZEROPAGE_Y},
	[0xC6] = {dec, OPERAND_ZEROPAGE},
	[0xD6] = {dec, OPERAND_ZEROPAGE_X},
	[0xCE] = {dec, OPERAND_ABSOLUTE},
	[0xDE] = {dec, OPERAND_ABSOLUTE_X},
	[0xCA] = {dex, OPERAND_IMPLIED},
	[0x88] = {dey, OPERAND_IMPLIED},
	[0xE6] = {inc, OPERAND_ZEROPAGE},
	[0xF6] = {inc, OPERAND_ZEROPAGE_X},
	[0xEE] = {inc, OPERAND_ABSOLUTE},
	[0xFE] = {inc, OPERAND_ABSOLUTE_X},
	[0xE8] = {inx, OPERAND_IMPLIED},
	[0xC8] = {iny, OPERAND_IMPLIED},
	[0x00] = {brk, OPERAND_IMPLIED},
	[0x4C] = {jmp, OPERAND_ABSOLUTE},
	[0x6C] = {jmp, OPERAND_INDIRECT},
	[0x20] = {jsr, OPERAND_ABSOLUTE},
	[0x40] = {rti, OPERAND_IMPLIED},
	[0x60] = {rts, OPERAND_IMPLIED},
	[0x90] = {bcc, OPERAND_RELATIVE},
	[0xB0] = {bcs, OPERAND_RELATIVE},
	[0xF0] = {beq, OPERAND_RELATIVE},
	[0x30] = {bmi, OPERAND_RELATIVE},
	[0xD0] = {bne, OPERAND_RELATIVE},
	[0x10] = {bpl, OPERAND_RELATIVE},
	[0x50] = {bvc, OPERAND_RELATIVE},
	[0x70] = {bvs, OPERAND_RELATIVE},
	[0x18] = {clc, OPERAND_IMPLIED},
	[0xD8] = {cld, OPERAND_IMPLIED},
	[0x58] = {cli, OPERAND_IMPLIED},
	[0xB8] = {clv, OPERAND_IMPLIED},
	[0x38] = {sec, OPERAND_IMPLIED},
	[0xF8] = {sed, OPERAND_IMPLIED},
	[0x78] = {sei, OPERAND_IMPLIED},
	[0xEA] = {nop, OPERAND_IMPLIED}
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

void push(struct cpu *cpu, uint8_t value, uint8_t *memory) {
	memory[0x100 + cpu->sp] = value;
	cpu->sp--;
}

void pull(struct cpu *cpu, uint8_t *dest, uint8_t *memory) {
	cpu->sp++;
	*dest = memory[0x100 + cpu->sp];
}
