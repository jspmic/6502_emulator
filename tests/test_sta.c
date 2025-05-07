#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/header.h"

START_TEST (test_fn_sta_zp)
{
	Byte addr = 0xFA, value=0xDE;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));

	reset(cpu, mem);
	cpu->a = value;
	mem->data[cpu->pc] = INS_STA_ZP;
	mem->data[(cpu->pc)+1] = addr;

	execute(cpu, mem, CCL_ST_ZP);
	ck_assert(mem->data[addr] == value);

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_fn_sta_zpx)
{
	Byte addr = 0xFA, value=0xDE, offset = 0x1A;
	Byte result_addr = addr+offset;
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));

	reset(cpu, mem);
	cpu->a = value;
	cpu->x = offset;
	mem->data[cpu->pc] = INS_STA_ZPX;
	mem->data[(cpu->pc)+1] = addr;

	execute(cpu, mem, CCL_ST_ZPX);
	ck_assert(mem->data[result_addr] == value);

	free_resource(&cpu, &mem);
}
END_TEST

Suite* fn_sta_suite (void){
	init();
	Suite* s;
	TCase *tc_core;
	s = suite_create("fn_STA");
	tc_core = tcase_create("fn_STA_testcase");
	tcase_add_test(tc_core, test_fn_sta_zp);
	tcase_add_test(tc_core, test_fn_sta_zpx);
	suite_add_tcase(s, tc_core);
	return s;
}
