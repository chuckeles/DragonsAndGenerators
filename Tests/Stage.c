#include "Stage.h"
#include "Tests.h"

/*
 * Test for creation and deletion of stages.
 */
START_TEST(StagesCreateTest)
{

  // create stages
  Stage* stages = CreateStages("C", 1, 1);

  // check them
  ck_assert_int_ne(stages, NULL);

  // delete stages
  DeleteStages(stages);

}
END_TEST

/*
 * Test for stage depth.
 */
START_TEST(StagesDepthTest)
  {

    // create stages
    Stage* stages = CreateStages("C", 1, 1);

    // check the depth
    ck_assert_int_ne(stages[HistoryAll - 1].tiles, NULL);

    // delete stages
    DeleteStages(stages);

  }
END_TEST

/*
 * Test for initialization of the first stage.
 */
START_TEST(StagesFirstTest)
  {

    // make a map
    char* map = "CCCC";

    // create stages
    Stage* stages = CreateStages(map, 2, 2);

    // check the first stage
    ck_assert_int_eq(stages[0].history, HistoryEmpty);
    ck_assert_int_eq(strcmp(stages[0].tiles, map), 0);
    ck_assert_int_eq(stages[0].paths[3], 0);
    ck_assert_int_eq(stages[0].directions[3], 0);

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
  tcase_add_test(tcase, StagesDepthTest);
  tcase_add_test(tcase, StagesFirstTest);

  // return the test case
  return tcase;

}
