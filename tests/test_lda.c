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

	execute(cpu, mem);
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

	execute(cpu, mem);
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

	mem->data[cpu->pc] = INS_LDA_ZP;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr] = value;

	execute(cpu, mem);
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

	mem->data[cpu->pc] = INS_LDA_ZPX;
	mem->data[(cpu->pc)+1] = addr;
	cpu->x = offset;
	mem->data[addr+offset] = value;

	execute(cpu, mem);
	ck_assert((cpu->a)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_lda_ab)
{
	Word addr = 0xDFF4;
	Byte value = 0xDE;
	Byte LSB = 0xF4;
	Byte MSB = 0xDF;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	mem->data[cpu->pc] = INS_LDA_AB;
	mem->data[(cpu->pc)+1] = LSB;
	mem->data[(cpu->pc)+2] = MSB;
	mem->data[addr] = value;

	execute(cpu, mem);
	ck_assert((cpu->a)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_lda_abx)
{
	Word addr = 0xDFF4, offset = 0x0005;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	cpu->x = offset;
	mem->data[cpu->pc] = INS_LDA_ABX;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr+offset] = value;

	execute(cpu, mem);
	ck_assert((cpu->a)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_lda_aby)
{
	Word addr = 0xDFE5, offset = 0x0012;
	Byte value = 0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	cpu->y = offset;
	mem->data[cpu->pc] = INS_LDA_ABY;
	mem->data[(cpu->pc)+1] = addr;
	mem->data[addr+offset] = value;

	execute(cpu, mem);
	ck_assert((cpu->a)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_lda_indX)
{
	Byte addr = 0xAF, offset = 0x12;
	Byte lsb = 0x11, msb = 0x22;
	Byte value = 0xDE;
	Word value_addr = 0x2211; // MSB-LSB combo
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	mem->data[cpu->pc] = INS_LDA_INDX;
	mem->data[(cpu->pc)+1] = addr;
	cpu->x = offset;
	mem->data[addr+offset] = lsb;
	mem->data[addr+offset+1] = msb;
	mem->data[value_addr] = value;

	execute(cpu, mem);
	ck_assert((cpu->a)==value);
	ck_assert((cpu->Z)==0x0);
	ck_assert((cpu->N)==0x1);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_lda_indY)
{
	Byte addr = 0xAF, offset = 0x12;
	Byte lsb = 0x11, msb = 0x22;
	Byte value = 0xDE;
	Word value_addr = 0x2211; // MSB-LSB combo
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);

	mem->data[cpu->pc] = INS_LDA_INDY;
	mem->data[(cpu->pc)+1] = addr;
	cpu->y = offset;
	mem->data[addr+offset] = lsb;
	mem->data[addr+offset+1] = msb;
	mem->data[value_addr] = value;

	execute(cpu, mem);
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
	tcase_add_test(tc_core, test_fn_lda_ab);
	tcase_add_test(tc_core, test_fn_lda_abx);
	tcase_add_test(tc_core, test_fn_lda_aby);
	tcase_add_test(tc_core, test_fn_lda_indX);
	tcase_add_test(tc_core, test_fn_lda_indY);
	suite_add_tcase(s, tc_core);
	return s;
}
