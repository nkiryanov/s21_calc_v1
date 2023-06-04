#ifndef SRC_TESTS_TEST_SUITES_H_
#define SRC_TESTS_TEST_SUITES_H_

#include <check.h>

Suite *make_master_suite(void);
Suite *make_suite_calc_deque(void);
Suite *make_suite_tokenize_once_function(void);
Suite *make_suite_tokenize_expression(void);
Suite *make_shunting_yard_suite(void);

#endif  // SRC_TESTS_TEST_SUITES_H_
