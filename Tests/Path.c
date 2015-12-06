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
    ck_assert_int_eq(stages[HistoryEmpty].directions[i], i > 0 ? 3 : 0);
  }

  // delete path and stages
  DeletePath(path);
  DeleteStages(stages);

}
END_TEST

/*
 * Simple path-finding test with an obstacle.
 */
START_TEST(SimplePathObstacleTest)
{

  // bloody iterator
  ushort i;

  // make stages
  Stage* stages = CreateStages("ccncc", 5, 1);

  // get the path
  uint length;
  int* path = FindPath(stages, 5, 1, &length);

  // check the path in the first stage
  for (i = 0; i < 2; ++i) {
    ck_assert_int_eq(stages[HistoryEmpty].paths[i], i + 1);
  }
  for (i = 2; i < 5; ++i) {
    ck_assert_int_eq(stages[HistoryEmpty].paths[i], 0);
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
    ck_assert_int_eq(stages[HistoryEmpty].directions[i], i > 0 ? 3 : 0);
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
    ck_assert_int_eq(stages[HistoryEmpty].directions[i], i > 0 ? 3 : 0);
  }

  // check the path in the dragon stage
  for (i = 2; i < 5; ++i) {
    ck_assert_int_eq(stages[HistoryDragon].paths[i], i + 1);
    ck_assert_int_eq(stages[HistoryDragon].directions[i], 3);
  }

  // delete path and stages
  DeletePath(path);
  DeleteStages(stages);

}
END_TEST

/*
 * Simple path-finding test with a generator.
 */
START_TEST(SimplePathGeneratorTest)
{

  // bloody iterator
  ushort i;

  // make stages
  Stage* stages = CreateStages("ccgcc", 5, 1);

  // get the path
  uint length;
  int* path = FindPath(stages, 5, 1, &length);

  // check the path in the first stage
  for (i = 0; i < 3; ++i) {
    ck_assert_int_eq(stages[HistoryEmpty].paths[i], i + 1);
    ck_assert_int_eq(stages[HistoryEmpty].directions[i], i > 0 ? 3 : 0);
  }

  // check the path in the dragon stage
  for (i = 2; i < 5; ++i) {
    ck_assert_int_eq(stages[HistoryGenerator].paths[i], i + 1);
    ck_assert_int_eq(stages[HistoryGenerator].directions[i], 3);
  }

  // delete path and stages
  DeletePath(path);
  DeleteStages(stages);

}
END_TEST

/*
 * Simple path-finding test with a forest.
 */
START_TEST(SimplePathForestTest)
{

  // bloody iterator
  ushort i;

  // make stages
  Stage* stages = CreateStages("hhhh", 4, 1);

  // get the path
  uint length;
  int* path = FindPath(stages, 4, 1, &length);

  // check the path in the first stage
  for (i = 0; i < 4; ++i) {
    ck_assert_int_eq(stages[HistoryEmpty].paths[i], (i + 1) * 2);
    ck_assert_int_eq(stages[HistoryEmpty].directions[i], i > 0 ? 3 : 0);
  }

  // delete path and stages
  DeletePath(path);
  DeleteStages(stages);

}
END_TEST

/*
 * Simple path-finding test with a dragon and a princess.
 */
START_TEST(SimplePathDragonPrincessTest)
{

  // bloody iterator
  ushort i;

  // make stages
  Stage* stages0 = CreateStages("cpcdc", 5, 1);
  Stage* stages1 = CreateStages("cqcdc", 5, 1);
  Stage* stages2 = CreateStages("crcdc", 5, 1);

  // get the path
  uint length;
  int* path0 = FindPath(stages0, 5, 1, &length);
  int* path1 = FindPath(stages1, 5, 1, &length);
  int* path2 = FindPath(stages2, 5, 1, &length);

  // check the path in the first stage
  for (i = 0; i < 4; ++i) {
    ck_assert_int_eq(stages0[HistoryEmpty].paths[i], i + 1);
    ck_assert_int_eq(stages0[HistoryEmpty].directions[i], i > 0 ? 3 : 0);
    ck_assert_int_eq(stages1[HistoryEmpty].paths[i], i + 1);
    ck_assert_int_eq(stages1[HistoryEmpty].directions[i], i > 0 ? 3 : 0);
    ck_assert_int_eq(stages2[HistoryEmpty].paths[i], i + 1);
    ck_assert_int_eq(stages2[HistoryEmpty].directions[i], i > 0 ? 3 : 0);
  }

  // check the path in the dragon stage
  for (i = 1; i < 4; ++i) {
    ck_assert_int_eq(stages0[HistoryDragon].paths[i], 7 - i);
    ck_assert_int_eq(stages0[HistoryDragon].directions[i], i < 3 ? 0 : 3);
    ck_assert_int_eq(stages1[HistoryDragon].paths[i], 7 - i);
    ck_assert_int_eq(stages1[HistoryDragon].directions[i], i < 3 ? 0 : 3);
    ck_assert_int_eq(stages2[HistoryDragon].paths[i], 7 - i);
    ck_assert_int_eq(stages2[HistoryDragon].directions[i], i < 3 ? 0 : 3);
  }

  // check the path in the princess stage
  for (i = 1; i < 5; ++i) {
    ck_assert_int_eq(stages0[HistoryDragon | HistoryPrincess0].paths[i], i + 5);
    ck_assert_int_eq(stages0[HistoryDragon | HistoryPrincess0].directions[i], i > 1 ? 3 : 0);
    ck_assert_int_eq(stages1[HistoryDragon | HistoryPrincess1].paths[i], i + 5);
    ck_assert_int_eq(stages1[HistoryDragon | HistoryPrincess1].directions[i], i > 1 ? 3 : 0);
    ck_assert_int_eq(stages2[HistoryDragon | HistoryPrincess2].paths[i], i + 5);
    ck_assert_int_eq(stages2[HistoryDragon | HistoryPrincess2].directions[i], i > 1 ? 3 : 0);
  }

  // delete path and stages
  DeletePath(path2);
  DeletePath(path1);
  DeletePath(path0);
  DeleteStages(stages2);
  DeleteStages(stages1);
  DeleteStages(stages0);

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
  tcase_add_test(tcase, SimplePathObstacleTest);
  tcase_add_test(tcase, SimplePathPrincessTest);
  tcase_add_test(tcase, SimplePathDragonTest);
  tcase_add_test(tcase, SimplePathGeneratorTest);
  tcase_add_test(tcase, SimplePathForestTest);
  tcase_add_test(tcase, SimplePathDragonPrincessTest);

  // return the test case
  return tcase;

}
