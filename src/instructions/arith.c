#include "cpu.h"
#include "instructions/instructions.h"

void adc(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	uint8_t acold = cpu->ac;
	uint8_t carryin = cpu->sr & SR_C;
	uint8_t achigh, aclow, ophigh, oplow, dechigh, declow;

	if (!(cpu->sr & SR_D)) {
		if (cpu->ac + *operand + carryin > 255)
			cpu->sr |= SR_C;
		else
			cpu->sr &= ~SR_C;

		cpu->ac += *operand + carryin;
	}
	else {
		achigh = cpu->ac >> 4;
		aclow = cpu->ac & 0xF;

		ophigh = *operand >> 4;
		oplow = *operand & 0xF;

		declow = aclow + oplow + carryin;
		dechigh = achigh + ophigh;
		if (declow > 9) {
			dechigh++;
			declow -= 10;
		}
		if (dechigh > 9) {
			cpu->sr |= SR_C;
			dechigh -= 10;
		}
		else
			cpu->sr &= ~SR_C;

		cpu->ac = dechigh << 4 | declow;
	}

	set_n_if_negative(cpu, cpu->ac);
	set_z_if_zero(cpu, cpu->ac);
	set_v_on_overflow(cpu, acold, *operand, carryin);
}

void cmp(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	uint8_t result = cpu->ac - *operand;

	if (result <= cpu->ac)
		cpu->sr |= SR_C;
	else
		cpu->sr &= ~SR_C;

	set_n_if_negative(cpu, result);
	set_z_if_zero(cpu, result);
}

void cpx(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	uint8_t result = cpu->x - *operand;

	if (result <= cpu->x)
		cpu->sr |= SR_C;
	else
		cpu->sr &= ~SR_C;

	set_n_if_negative(cpu, result);
	set_z_if_zero(cpu, result);
}

void cpy(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	uint8_t result = cpu->y - *operand;

	if (result <= cpu->y)
		cpu->sr |= SR_C;
	else
		cpu->sr &= ~SR_C;

	set_n_if_negative(cpu, result);
	set_z_if_zero(cpu, result);
}

void sbc(struct cpu *cpu, uint8_t *operand, uint8_t *) {
	uint8_t not_operand = ~*operand;
	if (!(cpu->sr & SR_D))
		adc(cpu, &not_operand, nullptr);
	else {
		uint8_t acold = cpu->ac;
		uint8_t carryin = cpu->sr & SR_C;
		int8_t achigh, aclow, ophigh, oplow, dechigh, declow;

		achigh = cpu->ac >> 4;
		aclow = cpu->ac & 0xF;

		ophigh = *operand >> 4;
		oplow = *operand & 0xF;

		declow = aclow + ~oplow + carryin;
		dechigh = achigh + ~ophigh;
		if (declow < 0) {
			// I'm not decrementing dechigh because of the natural behaviour of two's complement.
			declow += 10;
		}
		if (dechigh < 0) {
			cpu->sr &= ~SR_C;
			dechigh += 10;
		}
		else
			cpu->sr &= ~SR_C;

		cpu->ac = dechigh << 4 | declow;
		set_n_if_negative(cpu, cpu->ac);
		set_z_if_zero(cpu, cpu->ac);
		set_v_on_overflow(cpu, acold, not_operand, carryin);
	}
}
