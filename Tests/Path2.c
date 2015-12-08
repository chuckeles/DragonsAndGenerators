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
 * Path-finding test with a simple resulting path.
 */
START_TEST(PathResultLongerTest)
{

  // create stages
  Stage* stages = CreateStages("cdcprq", 2, 3);

  // find the path
  uint length;
  int* path = FindPath(stages, 2, 3, &length);

  // check the length
  ck_assert_int_eq(length, 5);

  // check the path
  ck_assert_int_eq(path[0], 0);
  ck_assert_int_eq(path[1], 0);
  ck_assert_int_eq(path[2], 1);
  ck_assert_int_eq(path[3], 0);
  ck_assert_int_eq(path[4], 1);
  ck_assert_int_eq(path[5], 1);
  ck_assert_int_eq(path[6], 1);
  ck_assert_int_eq(path[7], 2);
  ck_assert_int_eq(path[8], 0);
  ck_assert_int_eq(path[9], 2);

  // delete path and stages
  DeletePath(path);
  DeleteStages(stages);

}
END_TEST

/*
 * Path-finding test with multiple resulting paths.
 */
START_TEST(PathDirectionTest)
{

  // create stages
  Stage* stages = CreateStages("ccccdpcqr", 3, 3);

  // find the path
  uint length;
  int* path = FindPath(stages, 3, 3, &length);

  // check the length
  ck_assert_int_eq(length, 6);

  // check the path
  ck_assert_int_eq(path[0], 0);
  ck_assert_int_eq(path[1], 0);
  ck_assert_int_eq(path[4], 1);
  ck_assert_int_eq(path[5], 1);
  ck_assert_int_eq(path[8], 2);
  ck_assert_int_eq(path[9], 2);

  // delete path and stages
  DeletePath(path);
  DeleteStages(stages);

}
END_TEST

/*
 * Standard test #1.
 */
START_TEST(StandardPathTest1)
{

  // create stages
  Stage* stages = CreateStages("hhhphqchhccchrcchchdhcchc", 5, 5);

  // find the path
  uint length = 0;
  int* path = FindPath(stages, 5, 5, &length);

  // check the length
  ck_assert_int_eq(length, 16);

  // delete path and stages
  DeletePath(path);
  DeleteStages(stages);

}
END_TEST

/*
 * Standard test #2.
 */
START_TEST(StandardPathTest2)
{

  // create stages
  Stage* stages = CreateStages("ccchhphcchhhchhchchhdhhhchhchchhccqhchhhhhcrhchhh", 7, 7);

  // find the path
  uint length = 0;
  int* path = FindPath(stages, 7, 7, &length);

  // check the length
  ck_assert_int_eq(length, 24);

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
  tcase_add_test(tcase, PathResultLongerTest);
  tcase_add_test(tcase, PathDirectionTest);
  tcase_add_test(tcase, StandardPathTest1);
  tcase_add_test(tcase, StandardPathTest2);

  // return the test case
  return tcase;

}
