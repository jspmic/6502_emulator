#include "header.h"
#include <stdlib.h>
#include <assert.h>

function_manager* manager;

void subscribe(f_instruction f, Byte opcode){
	manager->functions[opcode] = f;
}

void execute_instruction(Byte opcode, u32* cycles, CPU* cpu, Memory* mem){
	manager->functions[opcode](cycles, cpu, mem);
}

void fn_lda_im(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->a);
	im(cycles, cpu, mem, &addr);
	LDSet(cpu);
}

void fn_lda_zp(u32 *cycles, CPU* cpu, Memory* mem){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address
	Byte addr_value = read_without_pc(cycles, operand, mem);
	cpu->a = addr_value;
	LDSet(cpu);
}

void fn_lda_zpx(u32 *cycles, CPU* cpu, Memory* mem){
	Byte operand = fetch_byte(cycles, cpu, mem); // Zero Page address

	// If the sum exceeds 1 byte, it will truncate it
	operand += (cpu->x);
	(*cycles)--;

	Byte addr_value = read_without_pc(cycles, operand, mem);
	cpu->a = addr_value;
	LDSet(cpu);
}

void fn_lda_ab(u32 *cycles, CPU* cpu, Memory* mem){
	Word operandW = fetch_word(cycles, cpu, mem); // Absolute address
	Byte addr_value = read_without_pc(cycles, operandW, mem);
	cpu->a = addr_value;
	LDSet(cpu);
}

void fn_lda_abx(u32 *cycles, CPU* cpu, Memory* mem){
	Word operandW = fetch_word(cycles, cpu, mem); // Absolute address
	operandW += (cpu->x);
	(*cycles)--;

	Byte addr_value = read_without_pc(cycles, operandW, mem);
	cpu->a = addr_value;
	LDSet(cpu);
}

void fn_ldx_im(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->x);
	im(cycles, cpu, mem, &addr);
	cpu->Z = (cpu->x) == 0;
	cpu->N = ((cpu->x) & 0b01000000) > 0;
}

void fn_ldy_im(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->y);
	im(cycles, cpu, mem, &addr);
	cpu->Z = (cpu->y) == 0;
	cpu->N = ((cpu->y) & 0b01000000) > 0;
}

void fn_jsr(u32 *cycles, CPU* cpu, Memory* mem){
	Word operandW = fetch_word(cycles, cpu, mem); // Subroutine address

	write_word(--(cpu->pc), cpu->sp, cycles, mem);
	cpu->sp++;
	cpu->pc = operandW;
	(*cycles)--;
}

void init(void){
	manager = malloc(sizeof(function_manager));
	manager->init = 0b1;
	subscribe(fn_lda_im, INS_LDA_IM);
	subscribe(fn_lda_zp, INS_LDA_ZP);
	subscribe(fn_lda_zpx, INS_LDA_ZPX);
	subscribe(fn_lda_ab, INS_LDA_AB);
	subscribe(fn_lda_abx, INS_LDA_ABX);
	subscribe(fn_ldx_im, INS_LDX_IM);
	subscribe(fn_ldy_im, INS_LDY_IM);
	subscribe(fn_jsr, INS_JSR);
}
