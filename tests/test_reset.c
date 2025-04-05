#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/header.h"

bool test_memory_reset(Memory* mem){
	for (int i = 0; i < MEM; i++){
		if ((mem->data)[i] != 0)
			return false;
	}
	return true;
}

START_TEST (test_reset)
{
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	reset(cpu, mem);
	ck_assert((cpu->pc) == 0xFFFC);
	ck_assert((cpu->sp) == 0x00);
	ck_assert((cpu->D) == 0);
	ck_assert((cpu->I) == 0);
	ck_assert_msg(test_memory_reset(mem),
			"Memory is not properly reset");

	free_resource(&cpu, &mem);
}
END_TEST

START_TEST (test_free_resource)
{
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	free_resource(&cpu, &mem);
	ck_assert_msg(cpu == NULL && mem == NULL, "Resources not properly freed");
}
END_TEST

Suite* reset_suite (void){
	Suite* s;
	TCase *tc_core;
	s = suite_create("reset");
	tc_core = tcase_create("reset_testcase");
	tcase_add_test(tc_core, test_reset);
	tcase_add_test(tc_core, test_free_resource);
	suite_add_tcase(s, tc_core);
	return s;
}
