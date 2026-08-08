#include <assert.h>
#include "header.h"

/* Immediate addressing mode
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void im(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Byte operand = fetch_byte(cycles, cpu, mem);
	*(*dst) = operand;
}

/* Zero-page addressing mode for LD. instructions
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void zp(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address
	Byte addr_value = read_without_pc(cycles, operand, mem);
	*(*dst) = addr_value;
}

/* Zero-page addressing mode for ST. instructions
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- src: src address(usually a cpu register) */
void zp_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address of memory
	mem->data[operand] = *(src);
	(*cycles)--;
}

/* Zero-page indexed addressing mode for LD. instructions
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void zpx(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address

	// If the sum exceeds 1 byte, it will truncate it
	operand += (cpu->x);
	(*cycles)--;

	Byte addr_value = read_without_pc(cycles, operand, mem);
	*(*dst) = addr_value;
}

/* Zero-page indexed addressing mode for ST. instructions
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- src: source address(usually a cpu register) */
void zpx_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address

	// If the sum exceeds 1 byte, it will truncate it
	operand += (cpu->x);
	(*cycles)--;

	mem->data[operand] = *(src);
	(*cycles)--;
}

/* Zero-page, Y addressing mode
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void zpy(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address

	// If the sum exceeds 1 byte, it will truncate it
	operand += (cpu->y);
	(*cycles)--;

	Byte addr_value = read_without_pc(cycles, operand, mem);
	*(*dst) = addr_value;
}

/* Absolute addressing mode
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void ab(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Word operandW = fetch_word(cycles, cpu, mem); // Absolute address
	Byte addr_value = read_without_pc(cycles, operandW, mem);
	*(*dst) = addr_value;
}

/* Absolute, X addressing mode
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void abx(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Word operandW = fetch_word(cycles, cpu, mem); // Absolute address
	operandW += (cpu->x);
	(*cycles)--;

	Byte addr_value = read_without_pc(cycles, operandW, mem);
	*(*dst) = addr_value;
}

/* Absolute, Y addressing mode
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void aby(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Word operandW = fetch_word(cycles, cpu, mem); // Absolute address
	operandW += (cpu->y);
	(*cycles)--;

	Byte addr_value = read_without_pc(cycles, operandW, mem);
	*(*dst) = addr_value;
}

/* Indexed Indirect addressing mode
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void indX(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address

	// If the sum exceeds 1 byte, it will truncate it
	operand += (cpu->x);
	(*cycles)--;

	Byte LSB = read_without_pc(cycles, operand, mem);
	Byte MSB = read_without_pc(cycles, operand+1, mem);
	Word addr = (MSB<<8) | LSB;
	Byte addr_value = read_without_pc(cycles, addr, mem);
	*(*dst) = addr_value;
}

/* Indexed Indirect addressing mode for ST. instructions
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- src: source address(usually a cpu register) */
void indX_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address

	// If the sum exceeds 1 byte, it will truncate it
	operand += (cpu->x);
	(*cycles)--;

	Byte LSB = read_without_pc(cycles, operand, mem);
	Byte MSB = read_without_pc(cycles, operand+1, mem);
	Word addr = (MSB<<8) | LSB;
	mem->data[addr] = *src;
	(*cycles)--;
}

/* Indirect Indexed addressing mode
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void indY(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address

	// If the sum exceeds 1 byte, it will truncate it
	operand += (cpu->y);
	(*cycles)--;

	Byte LSB = read_without_pc(cycles, operand, mem);
	Byte MSB = read_without_pc(cycles, operand+1, mem);
	Word addr = (MSB<<8) | LSB;
	Byte addr_value = read_without_pc(cycles, addr, mem);
	*(*dst) = addr_value;
}

/* Indirect Indexed addressing mode for ST. instructions
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- src: source address(usually a cpu register) */
void indY_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address

	// If the sum exceeds 1 byte, it will truncate it
	operand += (cpu->y);
	(*cycles)--;

	Byte LSB = read_without_pc(cycles, operand, mem);
	Byte MSB = read_without_pc(cycles, operand+1, mem);
	Word addr = (MSB<<8) | LSB;
	mem->data[addr] = *src;
	(*cycles)--;
}

/* Absolute addressing mode
params:
- cycles: Instruction cycles
- cpu: the CPU struct
- mem: the Memory struct
- dst: destination address(usually a cpu register) */
void ab_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src){
	Word operandW = fetch_word(cycles, cpu, mem); // Absolute address
	mem->data[operandW] = *src;
	(*cycles)--;
}

void push_stack(u32* cycles, CPU* cpu, Memory* mem, Byte data){
	if ( (STACK_MAX+(cpu->S) - 1) < STACK_MAX) {
		perror("push_stack: stack overflow");
		return;
	}

	Word stack_addr = STACK_MAX + (cpu->S);

	cpu->S--;
	(*cycles)--;

	mem->data[stack_addr] = data;
	(*cycles)--;
}

void pull_stack(u32* cycles, CPU* cpu, Memory* mem, Byte* dest){
	if ( (STACK_MAX+(cpu->S) + 1) > STACK_MIN) {
		perror("pull_stack: memory inaccessible");
		return;
	}

	Byte data = mem->data[cpu->S + 1];
	(*cycles)--;

	cpu->S++;
	(*cycles)--;

	*dest = data;
	(*cycles)--; // for derefencing the destination
	(*cycles)--; // for copying the data to the destination
}

void transfer_r2r(u32* cycles, Byte* src, Byte* dest) {
	*dest = *src;
	(*cycles)--;
}
