#include "cpu.h"

void reset(struct cpu *cpu, uint8_t *memory) {
    cpu->pc = (memory[0xFFFD] << 8) | memory[0xFFFC];
}

void run(struct cpu *cpu, uint8_t *memory) {

}
