#include <stdio.h>
#include <memory.h>
#include <assert.h>
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

	if ((cpu->pc)+1 < MEM) {
		cpu->pc++;
	}
	else {
		cpu->pc = 0x0000;
	}

	(*cycles)--;
	return data;
}

/* Reads from the program counter and returns a Word value */
Word fetch_word(u32 *cycles, CPU* cpu, Memory* mem){
	// 6502: little endian
	Word data = mem->data[cpu->pc];
	if ((cpu->pc)+1 < MEM) {
		cpu->pc++;
	}
	else {
		cpu->pc = 0x0000;
	}

	data |= ((mem->data[cpu->pc]) << 8);

	if ((cpu->pc)+1 < MEM) {
		cpu->pc++;
	}
	else {
		cpu->pc = 0x0000;
	}

	(*cycles)-=2;
	return data;
}

void write_word(Word value, u32 addr, u32 *cycles, Memory* mem){
	mem->data[addr] = value & 0xFF;
	mem->data[++addr] = value >> 8;
	(*cycles)-=2;
}

void write_byte(Byte value, u32 addr, u32 *cycles, Memory* mem){
	mem->data[addr] = value;
	(*cycles)--;
}

Byte read_without_pc(u32 *cycles, Word address, Memory* mem){
	Byte data = mem->data[address];

	(*cycles)--;
	return data;
}

void LDSet(CPU* cpu, u32 dst){
	Byte target_reg;
	switch (dst){
		case REG_A:
			target_reg = cpu->a;
			break;
		case REG_X:
			target_reg = cpu->x;
			break;
		case REG_Y:
			target_reg = cpu->y;
			break;
		default:
			perror("LDSet");
			return;
	}
	cpu->Z = (target_reg) == 0;
	cpu->N = ((target_reg) & 0x40) > 0;
}

void execute(CPU* cpu, Memory* mem){
	for (;;) {
		u32 cycles = manager->cycles[mem->data[cpu->pc]];
		if (cycles == 0) {
			break;
		}

		for (;cycles > 0;){
			Byte instruction = fetch_byte(&cycles, cpu, mem);
			execute_instruction(instruction, &cycles, cpu, mem);
		}
	}
}

// For debugging
void print_memory(Memory* mem) {
	for (int i = 0; i < MEM; i++) {
		printf("%.4X  ==  %.2X\n", i, mem->data[i]);
	}
}
