#include <stdlib.h>
#include "header.h"

int main(){
	CPU *cpu = malloc(sizeof(CPU));
	Memory *mem = malloc(sizeof(Memory));
	reset(cpu, mem);
	fn_lda_im(0xDE, cpu, mem);
	free_resource(cpu, mem);
	return 0;
}
