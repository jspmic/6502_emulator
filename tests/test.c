#include "header.h"
#include <check.h>
#include <stdlib.h>

int main(void){
	int failed;
	Suite *s0, *s1, *s2, *s3;
	SRunner *sr;

	s0 = reset_suite();
	s1 = fn_lda_suite();
	s2 = fn_ldx_suite();
	s3 = fn_ldy_suite();
	sr = srunner_create(s0);
	srunner_add_suite(sr, s1);
	srunner_add_suite(sr, s2);
	srunner_add_suite(sr, s3);

	srunner_run_all(sr, CK_VERBOSE);
	failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
