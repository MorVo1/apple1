#include "cpu.h"

void brk(struct cpu *, uint8_t *, uint8_t *);
void jmp(struct cpu *, uint8_t *, uint8_t *);
void jsr(struct cpu *, uint8_t *, uint8_t *);
void rti(struct cpu *, uint8_t *, uint8_t *);
void rts(struct cpu *, uint8_t *, uint8_t *);

