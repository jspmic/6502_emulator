#include "header.h"
#include <stdlib.h>

void reset(CPU* cpu, Memory* mem){
	cpu->pc = 0xFFFC;
	cpu->sp = 0x00;
	cpu->D = 0;
	cpu->I = 0;
	mem = calloc(MEM, sizeof(Byte));
}
