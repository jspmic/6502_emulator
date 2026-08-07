#include <stdio.h>
#include <stdlib.h>
#include "src/header.h"

int main(int argc, char** argv){
	// Initialization code
	CPU* cpu = (CPU*) malloc(sizeof(CPU));
	Memory* mem = (Memory*) malloc(sizeof(Memory));
	reset(cpu, mem);

	// Loader code
	// File code expected result:
	// [0x200] <- 0xA1
	// [0x201] <- 0xF2
	// [0x202] <- 0xCA
	// **** tested ****

	char* name = "./examples/a.o65";
	FILE* file = read_binary(name);
	load_memory(file, mem, cpu);
	execute(cpu, mem);

	// Ending code
	close_binary(file);
	free_resource(&cpu, &mem);
	return 0;
}
