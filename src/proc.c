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

Byte read_without_pc(u32 *cycles, Byte address, Memory* mem){
	Byte data = mem->data[address];

	(*cycles)--;
	return data;
}

void LDSet(CPU* cpu){
	cpu->Z = (cpu->a) == 0;
	cpu->N = ((cpu->a) & 0b01000000) > 0;
}

void execute(CPU* cpu, Memory* mem, u32 cycles){
	for (;cycles > 0;){
		Byte instruction = fetch(&cycles, cpu, mem);
		Byte operand, addr_value;
		switch (instruction){
			case INS_LDA_IM:
				operand = fetch(&cycles, cpu, mem);
				cpu->a = operand;
				LDSet(cpu);
				break;
			case INS_LDX_IM:
				operand = fetch(&cycles, cpu, mem);
				cpu->x = operand;
				cpu->Z = (cpu->x) == 0;
				cpu->N = ((cpu->x) & 0b01000000) > 0;
				break;
			case INS_LDY_IM:
				operand = fetch(&cycles, cpu, mem);
				cpu->y = operand;
				cpu->Z = (cpu->y) == 0;
				cpu->N = ((cpu->y) & 0b01000000) > 0;
				break;
			case INS_LDA_ZP:
				operand = fetch(&cycles, cpu, mem); // Zero Page address
				addr_value = read_without_pc(&cycles, operand, mem);
				cpu->a = addr_value;
				LDSet(cpu);
				break;
			case INS_LDA_ZPX:
				operand = fetch(&cycles, cpu, mem); // Zero Page address

				// If the sum exceeds 1 byte, it will truncate it
				operand += (cpu->x);
				cycles--;

				addr_value = read_without_pc(&cycles, operand, mem);
				cpu->a = addr_value;
				LDSet(cpu);
				break;
			default:
				printf("Unexceptional case not handled: %d\n", instruction);
				break;
		}
	}
}
