#include "Path.h"
#include "Stage.h"
#include "Tests.h"

/*
 * Simple path-finding test.
 */
START_TEST(SimplePathTest)
{

  // make stages
  Stage* stages = CreateStages("ccccc", 5, 1);

  // get the path
  uint length;
  int* path = FindPath(stages, 5, 1, &length);

  // check the path in the first stage
  ushort i;
  for (i = 0; i < 5; ++i) {
    ck_assert_int_eq(stages[HistoryEmpty].paths[i], i + 1);
  }

  // delete path and stages
  DeletePath(path);
  DeleteStages(stages);

}
END_TEST

/*
 * Path-finding test case.
 */
TCase* PathTCase() {

  // create the test case
  TCase* tcase = tcase_create("Path");

  // add tests
  tcase_add_test(tcase, SimplePathTest);

  // return the test case
  return tcase;

}
