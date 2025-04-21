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
	LDSet(cpu, REG_A);
}

void fn_lda_zp(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->a);
	zp(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_A);
}

void fn_lda_zpx(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->a);
	zpx(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_A);
}

void fn_lda_ab(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->a);
	ab(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_A);
}

void fn_lda_abx(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->a);
	abx(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_A);
}

void fn_lda_aby(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->a);
	aby(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_A);
}

void fn_ldx_im(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->x);
	im(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_X);
}

void fn_ldy_im(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->y);
	im(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_Y);
}

void init(void){
	manager = malloc(sizeof(function_manager));
	manager->init = 0x1;
	subscribe(fn_lda_im, INS_LDA_IM);
	subscribe(fn_lda_zp, INS_LDA_ZP);
	subscribe(fn_lda_zpx, INS_LDA_ZPX);
	subscribe(fn_lda_ab, INS_LDA_AB);
	subscribe(fn_lda_abx, INS_LDA_ABX);
	subscribe(fn_lda_aby, INS_LDA_ABY);
	subscribe(fn_ldx_im, INS_LDX_IM);
	subscribe(fn_ldy_im, INS_LDY_IM);
}
