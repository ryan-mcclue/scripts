// SPDX-License-Identifier: zlib-acknowledgement

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <limits.h>
#include <cmocka.h>

extern void qemu_arm_exit(void);

extern int testable_main(void);

void
test_tem(void **state)
{
  assert_int_equal(testable_main(), 0);
}

int 
main(void)
{
	const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_tem),
  };

  int cmocka_res = cmocka_run_group_tests(tests, NULL, NULL);

  qemu_arm_exit();

  return cmocka_res;
}
