#include "History.h"
#include "Tests.h"

/*
 * Test for the History enum.
 */
START_TEST(HistoryTest) {

  // check the empty history
  ck_assert_int_eq(HistoryEmpty, 0);

  // check the full history
  ck_assert_int_eq(HistoryAll,
                   HistoryDragon | HistoryGenerator | HistoryPrincess0 | HistoryPrincess1 | HistoryPrincess2);

}
END_TEST

/*
 * History test case.
 */
TCase* HistoryTCase() {

  // create the test case
  TCase* tcase = tcase_create("History");

  // add tests
  tcase_add_test(tcase, HistoryTest);

  // return the test case
  return tcase;

}
