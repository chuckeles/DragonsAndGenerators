#include "Stage.h"
#include "Tests.h"

/*
 * Test for creation and deletion of stages.
 */
START_TEST(StagesCreateTest)
{

  // make up map size
  ushort width = 1;
  ushort height = 1;

  // create a map
  char* map = "C";

  // create stages
  Stage* stages = CreateStages(map, width, height);

  // check them
  ck_assert_int_ne(stages, NULL);

  // delete stages
  DeleteStages(stages);

}
END_TEST

/*
 * Stage test case.
 */
TCase* StageTCase() {

  // create the test case
  TCase* tcase = tcase_create("Stage");

  // add tests
  tcase_add_test(tcase, StagesCreateTest);

  // return the test case
  return tcase;

}
