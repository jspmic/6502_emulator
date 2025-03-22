#include <stdlib.h>
#include "header.h"

int main(){
	CPU *cpu = malloc(sizeof(CPU));
	Memory *mem = malloc(sizeof(Memory));
	reset(cpu, mem);
	return 0;
}
