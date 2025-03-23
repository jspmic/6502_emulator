#include <stdlib.h>
#include "header.h"

int main(){
	CPU *cpu = malloc(sizeof(CPU));
	Memory *mem = malloc(sizeof(Memory));
	reset(cpu, mem);
	u32 ad = 0xEF;
	mem->data[cpu->pc] = INS_LDA_ZP;
	mem->data[(cpu->pc)+1] = ad;
	mem->data[ad] = 0x0F;
	execute(cpu, mem, CCL_LD_ZP);
	return 0;
}
