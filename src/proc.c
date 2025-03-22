#include <memory.h>
#include <assert.h>
#include <stdio.h>
#include "header.h"

/* Resets the CPU and Memory according to 6502 indications */
void reset(CPU* cpu, Memory* mem){
	cpu->pc = 0xFFFC;
	cpu->sp = 0x00;
	cpu->D = 0;
	cpu->I = 0;
	memset(mem->data, 0, sizeof(mem->data));
}

Byte fetch(u32 *cycles, CPU* cpu, Memory* mem){
	Byte data = mem->data[cpu->pc];

	if ((cpu->pc)+1 < MEM)
		cpu->pc++;

	(*cycles)--;
	return data;
}

void execute(CPU* cpu, Memory* mem, u32 cycles){
	for (;cycles > 0;){
		Byte instruction = fetch(&cycles, cpu, mem);
		Byte value;
		switch (instruction){
			case INS_LDA_IM:
				value = fetch(&cycles, cpu, mem);
				cpu->a = value;
				cpu->Z = (cpu->a) == 0;
				cpu->N = ((cpu->a) & 0b01000000) > 0;
				break;
			case INS_LDX_IM:
				value = fetch(&cycles, cpu, mem);
				cpu->x = value;
				cpu->Z = (cpu->x) == 0;
				cpu->N = ((cpu->x) & 0b01000000) > 0;
				break;
			case INS_LDY_IM:
				value = fetch(&cycles, cpu, mem);
				cpu->y = value;
				cpu->Z = (cpu->y) == 0;
				cpu->N = ((cpu->y) & 0b01000000) > 0;
				break;
			default:
				printf("Default case: %d\n", instruction);
				break;
		}
	}
}
