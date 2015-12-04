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

  return 0;

}
