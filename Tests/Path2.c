#include "Path.h"
#include "Tests.h"

/*
 * Path-finding test with a simple resulting path.
 */
START_TEST(PathResultTest)
{

  // create stages
  Stage* stages = CreateStages("dpqr", 4, 1);

  // find the path
  uint length;
  int* path = FindPath(stages, 4, 1, &length);

  // check the length
  ck_assert_int_eq(length, 4);

  // check the path
  uint i;
  for (i = 0; i < length; ++i) {
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
TCase* Path2TCase() {

  // create the test case
  TCase* tcase = tcase_create("Path2");

  // add tests
  tcase_add_test(tcase, PathResultTest);

  // return the test case
  return tcase;

}
