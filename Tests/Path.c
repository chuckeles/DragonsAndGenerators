#include "Path.h"
#include "Stage.h"
#include "Tests.h"

/*
 * Simple path-finding test without a generator.
 */
START_TEST(SimplePathTest)
{

  // make stages
  Stage* stages = CreateStages("cdppp", 5, 1);

  // get the path
  uint length;
  int* path = FindPath(stages, 5, 1, &length);

  // check the length
  ck_assert_int_eq(length, 5);

  // check the path
  ushort i;
  for (i = 0; i < 5; ++i) {
    ck_assert_int_eq(path[i * 2], i);
    ck_assert_int_eq(path[i * 2 + 1], 0);
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
