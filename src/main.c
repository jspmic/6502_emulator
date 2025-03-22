#include <stdlib.h>
#include "header.h"

int main(){
	CPU *cpu = malloc(sizeof(CPU));
	Memory *mem = malloc(sizeof(Memory));
	reset(cpu, mem);
	mem->data[cpu->pc] = INS_LDA_ZPX;
	mem->data[(cpu->pc)+1] = 0x80;
	cpu->x = 0x0F;
	mem->data[0x8F] = 0xDE;
	execute(cpu, mem, CCL_LD_ZPX);
	return 0;
}
