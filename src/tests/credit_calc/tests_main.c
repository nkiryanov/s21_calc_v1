#include <check.h>
#include <stdlib.h>

#include "test_suites.h"

int main(void) {
  int number_failed;
  SRunner *sr;
  sr = srunner_create(make_master_suite());

  // We set NOFORK mode for debug ability and testing with valgrind
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_add_suite(sr, make_suite_get_credits_payments());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
