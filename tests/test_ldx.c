#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/header.h"

START_TEST (test_fn_ldx_im)
{
	Word c1 = 0b10000000;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));

	// First execution with cpu->N == 0
	reset(cpu, mem);
	mem->data[cpu->pc] = INS_LDX_IM;
	mem->data[(cpu->pc)+1] = c1;

	execute(cpu, mem);
	ck_assert((cpu->x)==c1);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x0);

	free_resource(&cpu, &mem);
}
END_TEST
START_TEST (test_fn_ldx_im_2)
{
	Word c2 = 0b01000000;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	// Second execution with cpu->N == 1
	mem->data[cpu->pc] = INS_LDX_IM;
	mem->data[(cpu->pc)+1] = c2;

	execute(cpu, mem);
	ck_assert((cpu->x)==c2);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_ldx_zp)
{
	Word addr = 0xF4;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	mem->data[cpu->pc] = INS_LDX_ZP;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr] = value;

	execute(cpu, mem);
	ck_assert((cpu->x)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_ldx_zpy)
{
	Word addr = 0xF4, offset = 0x01;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	mem->data[cpu->pc] = INS_LDX_ZPY;
	mem->data[(cpu->pc)+1] = addr;
	cpu->y = offset;
	mem->data[addr+offset] = value;

	execute(cpu, mem);
	ck_assert((cpu->x)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_ldx_ab)
{
	Word addr = 0xDFF4;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	mem->data[cpu->pc] = INS_LDX_AB;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr] = value;

	execute(cpu, mem);
	ck_assert((cpu->x)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_ldx_aby)
{
	Word addr = 0xDFE5, offset = 0x0012;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	cpu->y = offset;
	mem->data[cpu->pc] = INS_LDX_ABY;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr+offset] = value;

	execute(cpu, mem);
	ck_assert((cpu->x)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

Suite* fn_ldx_suite (void){
	Suite* s;
	TCase *tc_core;
	s = suite_create("fn_LDX");
	tc_core = tcase_create("fn_LDX_testcase");
	tcase_add_test(tc_core, test_fn_ldx_im);
	tcase_add_test(tc_core, test_fn_ldx_im_2);
	tcase_add_test(tc_core, test_fn_ldx_zp);
	tcase_add_test(tc_core, test_fn_ldx_zpy);
	tcase_add_test(tc_core, test_fn_ldx_ab);
	tcase_add_test(tc_core, test_fn_ldx_aby);
	suite_add_tcase(s, tc_core);
	return s;
}
