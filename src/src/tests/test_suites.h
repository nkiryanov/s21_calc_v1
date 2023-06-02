#ifndef SRC_TESTS_TEST_SUITES_H_
#define SRC_TESTS_TEST_SUITES_H_

#include <check.h>

Suite *make_master_suite(void);
Suite *make_suite_deque(void);
Suite *make_suite_match_token(void);
Suite *make_suite_validate(void);

#endif  // SRC_TESTS_TEST_SUITES_H_
