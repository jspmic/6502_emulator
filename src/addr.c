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

/* Zero-page addressing mode
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

/* Zero-page indexed addressing mode
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
