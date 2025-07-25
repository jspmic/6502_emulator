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

void fn_lda_indX(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->a);
	indX(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_A);
}

void fn_lda_indY(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->a);
	indY(cycles, cpu, mem, &addr);
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

void fn_ldx_zp(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->x);
	zp(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_X);
}

void fn_ldx_zpy(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->x);
	zpy(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_X);
}

void fn_ldx_ab(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->x);
	ab(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_X);
}

void fn_ldx_aby(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->x);
	aby(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_X);
}

void fn_ldy_im(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->y);
	im(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_Y);
}

void fn_ldy_zp(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->y);
	zp(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_Y);
}

void fn_ldy_zpx(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->y);
	zpx(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_Y);
}

void fn_ldy_ab(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->y);
	ab(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_Y);
}

void fn_ldy_abx(u32 *cycles, CPU* cpu, Memory* mem){
	Byte* addr = &(cpu->y);
	abx(cycles, cpu, mem, &addr);
	LDSet(cpu, REG_Y);
}

void fn_sta_zp(u32 *cycles, CPU* cpu, Memory* mem){
	zp_st(cycles, cpu, mem, &(cpu->a));
}

void fn_sta_zpx(u32 *cycles, CPU* cpu, Memory* mem){
	zpx_st(cycles, cpu, mem, &(cpu->a));
}

void fn_sta_indX(u32 *cycles, CPU* cpu, Memory* mem){
	indX_st(cycles, cpu, mem, &(cpu->a));
}

void fn_sta_indY(u32 *cycles, CPU* cpu, Memory* mem){
	indY_st(cycles, cpu, mem, &(cpu->a));
}

__attribute__((constructor)) void init(void){
	manager = malloc(sizeof(function_manager));
	manager->init = 0x1;
	subscribe(fn_lda_im, INS_LDA_IM);
	subscribe(fn_lda_zp, INS_LDA_ZP);
	subscribe(fn_lda_zpx, INS_LDA_ZPX);
	subscribe(fn_lda_ab, INS_LDA_AB);
	subscribe(fn_lda_abx, INS_LDA_ABX);
	subscribe(fn_lda_aby, INS_LDA_ABY);
	subscribe(fn_lda_indX, INS_LDA_INDX);
	subscribe(fn_lda_indY, INS_LDA_INDY);

	subscribe(fn_ldx_im, INS_LDX_IM);
	subscribe(fn_ldx_zp, INS_LDX_ZP);
	subscribe(fn_ldx_zpy, INS_LDX_ZPY);
	subscribe(fn_ldx_ab, INS_LDX_AB);
	subscribe(fn_ldx_aby, INS_LDX_ABY);

	subscribe(fn_ldy_im, INS_LDY_IM);
	subscribe(fn_ldy_zp, INS_LDY_ZP);
	subscribe(fn_ldy_zpx, INS_LDY_ZPX);
	subscribe(fn_ldy_ab, INS_LDY_AB);
	subscribe(fn_ldy_abx, INS_LDY_ABX);

	subscribe(fn_sta_zp, INS_STA_ZP);
	subscribe(fn_sta_zpx, INS_STA_ZPX);
	subscribe(fn_sta_indX, INS_STA_INDX);
	subscribe(fn_sta_indY, INS_STA_INDY);
}
