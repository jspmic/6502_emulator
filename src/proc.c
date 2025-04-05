#include <memory.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void free_resource(CPU** cpu, Memory** mem){
	free(*cpu);
	free(*mem);
	*cpu = NULL;
	*mem = NULL;
}

/* Resets the CPU and Memory according to 6502 indications */
void reset(CPU* cpu, Memory* mem){
	cpu->pc = 0xFFFC;
	cpu->sp = 0x00;
	cpu->D = 0;
	cpu->I = 0;
	memset(mem->data, 0, sizeof(mem->data));
}

/* Reads from the program counter and returns a Byte value */
Byte fetch_byte(u32 *cycles, CPU* cpu, Memory* mem){
	Byte data = mem->data[cpu->pc];

	if ((cpu->pc)+1 < MEM)
		cpu->pc++;

	(*cycles)--;
	return data;
}

/* Reads from the program counter and returns a Word value */
Word fetch_word(u32 *cycles, CPU* cpu, Memory* mem){
	// 6502: little endian
	Word data = mem->data[cpu->pc];
	if ((cpu->pc)+1 < MEM)
		cpu->pc++;

	data |= ((mem->data[cpu->pc]) << 8);

	if ((cpu->pc)+1 < MEM)
		cpu->pc++;

	(*cycles)-=2;
	return data;
}

void write_word(Word value, u32 addr, u32 *cycles, Memory* mem){
	mem->data[addr] = value & 0xFF;
	mem->data[++addr] = value >> 8;
	(*cycles)-=2;
}

Byte read_without_pc(u32 *cycles, Word address, Memory* mem){
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
		Byte instruction = fetch_byte(&cycles, cpu, mem);
		Byte operand, addr_value;
		Word operandW;
		switch (instruction){
			case INS_LDA_IM:
				operand = fetch_byte(&cycles, cpu, mem);
				cpu->a = operand;
				LDSet(cpu);
				break;
			case INS_LDX_IM:
				operand = fetch_byte(&cycles, cpu, mem);
				cpu->x = operand;
				cpu->Z = (cpu->x) == 0;
				cpu->N = ((cpu->x) & 0b01000000) > 0;
				break;
			case INS_LDY_IM:
				operand = fetch_byte(&cycles, cpu, mem);
				cpu->y = operand;
				cpu->Z = (cpu->y) == 0;
				cpu->N = ((cpu->y) & 0b01000000) > 0;
				break;
			case INS_LDA_ZP:
				operand = fetch_byte(&cycles, cpu, mem); // Zero Page address
				addr_value = read_without_pc(&cycles, operand, mem);
				cpu->a = addr_value;
				LDSet(cpu);
				break;
			case INS_LDA_ZPX:
				operand = fetch_byte(&cycles, cpu, mem); // Zero Page address

				// If the sum exceeds 1 byte, it will truncate it
				operand += (cpu->x);
				cycles--;

				addr_value = read_without_pc(&cycles, operand, mem);
				cpu->a = addr_value;
				LDSet(cpu);
				break;

			case INS_LDA_AB:
				operandW = fetch_word(&cycles, cpu, mem); // Absolute address
				addr_value = read_without_pc(&cycles, operandW, mem);
				cpu->a = addr_value;
				LDSet(cpu);
				break;

			case INS_LDA_ABX:
				operandW = fetch_word(&cycles, cpu, mem); // Absolute address
				operandW += (cpu->x);
				cycles--;

				addr_value = read_without_pc(&cycles, operandW, mem);
				cpu->a = addr_value;
				LDSet(cpu);
				break;

			case INS_JSR:
				operandW = fetch_word(&cycles, cpu, mem); // Subroutine address

				write_word(--(cpu->pc), cpu->sp, &cycles, mem);
				cpu->sp++;
				cpu->pc = operandW;
				cycles--;
				break;
			default:
				printf("Unexceptional case not handled: %d\n", instruction);
				break;
		}
	}
}
