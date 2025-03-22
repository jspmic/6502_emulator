#include <stdlib.h>
#include "header.h"

int main(){
	CPU *cpu = malloc(sizeof(CPU));
	Memory *mem = malloc(sizeof(Memory));
	reset(cpu, mem);
	mem->data[cpu->pc] = INS_LDA_IM;
	mem->data[(cpu->pc)+1] = 0b01000000;
	execute(cpu, mem, CCL_LD_IM);
	return 0;
}
