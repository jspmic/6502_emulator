#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/header.h"

START_TEST (test_fn_lda_im)
{
	Word c1 = 0b10000000;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));

	// First execution with cpu->N == 0
	reset(cpu, mem);
	mem->data[cpu->pc] = INS_LDA_IM;
	mem->data[(cpu->pc)+1] = c1;

	execute(cpu, mem, CCL_LD_IM);
	ck_assert((cpu->a)==c1);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x0);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_lda_im_2)
{
	Word c2 = 0b01000000;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	// Second execution with cpu->N == 1
	mem->data[cpu->pc] = INS_LDA_IM;
	mem->data[(cpu->pc)+1] = c2;

	execute(cpu, mem, CCL_LD_IM);
	ck_assert((cpu->a)==c2);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_lda_zp)
{
	Word addr = 0xF4;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	// Second execution with cpu->N == 1
	mem->data[cpu->pc] = INS_LDA_ZP;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr] = value;

	execute(cpu, mem, CCL_LD_ZP);
	ck_assert((cpu->a)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_lda_zpx)
{
	Word addr = 0xF4, offset = 0x01;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	// Second execution with cpu->N == 1
	mem->data[cpu->pc] = INS_LDA_ZPX;
	mem->data[(cpu->pc)+1] = addr;
	cpu->x = offset;
	mem->data[addr+offset] = value;

	execute(cpu, mem, CCL_LD_ZPX);
	ck_assert((cpu->a)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

Suite* fn_lda_suite (void){
	Suite* s;
	TCase *tc_core;
	s = suite_create("fn_LDA");
	tc_core = tcase_create("fn_LDA_testcase");
	tcase_add_test(tc_core, test_fn_lda_im);
	tcase_add_test(tc_core, test_fn_lda_im_2);
	tcase_add_test(tc_core, test_fn_lda_zp);
	tcase_add_test(tc_core, test_fn_lda_zpx);
	suite_add_tcase(s, tc_core);
	return s;
}
