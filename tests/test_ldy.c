#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/header.h"

START_TEST (test_fn_ldy_im)
{
	Word c1 = 0b10000000;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));

	// First execution with cpu->N == 0
	reset(cpu, mem);
	mem->data[cpu->pc] = INS_LDY_IM;
	mem->data[(cpu->pc)+1] = c1;

	execute(cpu, mem, CCL_LD_IM);
	ck_assert((cpu->y)==c1);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x0);

	free_resource(&cpu, &mem);
}
END_TEST
START_TEST (test_fn_ldy_im_2)
{
	Word c2 = 0b01000000;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	// Second execution with cpu->N == 1
	mem->data[cpu->pc] = INS_LDY_IM;
	mem->data[(cpu->pc)+1] = c2;

	execute(cpu, mem, CCL_LD_IM);
	ck_assert((cpu->y)==c2);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_ldy_zp)
{
	Word addr = 0xF4;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	mem->data[cpu->pc] = INS_LDY_ZP;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr] = value;

	execute(cpu, mem, CCL_LD_ZP);
	ck_assert((cpu->y)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_ldy_zpx)
{
	Word addr = 0xF4, offset = 0x01;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	mem->data[cpu->pc] = INS_LDY_ZPX;
	mem->data[(cpu->pc)+1] = addr;
	cpu->x = offset;
	mem->data[addr+offset] = value;

	execute(cpu, mem, CCL_LD_ZPX);
	ck_assert((cpu->y)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_ldy_ab)
{
	Word addr = 0xDFF4;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	mem->data[cpu->pc] = INS_LDY_AB;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr] = value;

	execute(cpu, mem, CCL_LD_AB);
	ck_assert((cpu->y)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_ldy_abx)
{
	Word addr = 0xDFF4, offset = 0x0005;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	cpu->x = offset;
	mem->data[cpu->pc] = INS_LDY_ABX;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr+offset] = value;

	execute(cpu, mem, CCL_LD_ABX);
	ck_assert((cpu->y)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}

Suite* fn_ldy_suite (void){
	Suite* s;
	TCase *tc_core;
	s = suite_create("fn_LDY");
	tc_core = tcase_create("fn_LDY_testcase");
	tcase_add_test(tc_core, test_fn_ldy_im);
	tcase_add_test(tc_core, test_fn_ldy_im_2);
	tcase_add_test(tc_core, test_fn_ldy_zp);
	tcase_add_test(tc_core, test_fn_ldy_zpx);
	tcase_add_test(tc_core, test_fn_ldy_ab);
	tcase_add_test(tc_core, test_fn_ldy_abx);
	suite_add_tcase(s, tc_core);
	return s;
}
