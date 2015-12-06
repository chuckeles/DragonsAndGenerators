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
 * Simple path-finding test with a dragon.
 */
START_TEST(SimplePathDragonTest)
{

  // bloody iterator
  ushort i;

  // make stages
  Stage* stages = CreateStages("ccdcc", 5, 1);

  // get the path
  uint length;
  int* path = FindPath(stages, 5, 1, &length);

  // check the path in the first stage
  for (i = 0; i < 3; ++i) {
    ck_assert_int_eq(stages[HistoryEmpty].paths[i], i + 1);
  }

  // check the path in the dragon stage
  for (i = 2; i < 5; ++i) {
    ck_assert_int_eq(stages[HistoryDragon].paths[i], i + 1);
  }

  // delete path and stages
  DeletePath(path);
  DeleteStages(stages);

}
END_TEST

/*
 * Simple path-finding test with a single princess.
 */
START_TEST(SimplePathPrincessTest)
{

  // make stages
  Stage* stages = CreateStages("ccpcc", 5, 1);

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
  tcase_add_test(tcase, SimplePathDragonTest);

  // return the test case
  return tcase;

}
