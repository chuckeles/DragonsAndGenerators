/*
 * Copyright (C) Chuckeles
 *
 * For license information, check the LICENSE.md file.
 */

#include <check.h>
#include <stdlib.h>

#include "History.h"

/*
 * Tests for the History enum.
 */
START_TEST(HistoryTest)
{

  // check the empty history
  ck_assert_int_eq(HistoryEmpty, 0);

  // check the full history
  ck_assert_int_eq(HistoryAll,
                   HistoryDragon | HistoryGenerator | HistoryPrincess0 | HistoryPrincess1 | HistoryPrincess2);

}
END_TEST

/*
 * Testing entry point.
 */
int main() {

  // create suite and test case
  Suite* suite = suite_create("History");
  TCase* tcase = tcase_create("Main");

  // add test
  tcase_add_test(tcase, HistoryTest);
  suite_add_tcase(suite, tcase);

  // create a runner
  SRunner* srunner = srunner_create(suite);

  // run tests
  srunner_run_all(srunner, CK_NORMAL);
  int failed = srunner_ntests_failed(srunner);

  // free
  srunner_free(srunner);

  return failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;

}
