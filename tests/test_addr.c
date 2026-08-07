#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/header.h"

START_TEST (test_push_stack)
{
	CPU* cpu = malloc(sizeof(CPU));
	Memory* mem = malloc(sizeof(Memory));
	u32* cycles = malloc(sizeof(u32));

	*cycles = 3;

	Byte data1 = 0x2F;
	Byte data2 = 0x30;
	Byte data3 = 0x4D;
	Byte data4 = 0x5C;
	cycles--;

	reset(cpu, mem);

	push_stack(cycles, cpu, mem, data1);
	push_stack(cycles, cpu, mem, data2);
	push_stack(cycles, cpu, mem, data3);
	push_stack(cycles, cpu, mem, data4);

	ck_assert((mem->data[STACK_MAX + cpu->S + 1]) == data4);
	ck_assert((mem->data[STACK_MAX + cpu->S + 2]) == data3);
	ck_assert((mem->data[STACK_MAX + cpu->S + 3]) == data2);
	ck_assert((mem->data[STACK_MAX + cpu->S + 4]) == data1);

	free_resource(&cpu, &mem);
}
END_TEST

Suite* fn_addr_suite (void){
	Suite* s;
	TCase *tc_core;
	s = suite_create("fn_addr");
	tc_core = tcase_create("fn_addr_testcase");
	tcase_add_test(tc_core, test_push_stack);
	suite_add_tcase(s, tc_core);
	return s;
}
