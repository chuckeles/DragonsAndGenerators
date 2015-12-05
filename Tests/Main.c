/*
 * Copyright (C) Chuckeles
 *
 * For license information, check the LICENSE.md file.
 */

#include <stdlib.h>

#include "Tests.h"

/*
 * Testing entry point.
 */
int main() {

  // create suite and test cases
  Suite* suite = suite_create("Main");
  TCase* historyCase = HistoryTCase();
  TCase* heapCase = HeapTCase();

  // add test cases to suite
  suite_add_tcase(suite, historyCase);
  suite_add_tcase(suite, heapCase);

  // create a runner
  SRunner* srunner = srunner_create(suite);

  // run tests
  srunner_run_all(srunner, CK_NORMAL);
  int failed = srunner_ntests_failed(srunner);

  // free
  srunner_free(srunner);

  // done
  return failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;

}
