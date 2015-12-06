#include "Stage.h"
#include "Tests.h"

/*
 * Test for creation and deletion of stages.
 */
START_TEST(StagesCreateTest)
{

  // create stages
  Stage* stages = CreateStages("c", 1, 1);

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
  Stage* stages = CreateStages("c", 1, 1);

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
  char* map = "cccc";

  // create stages
  Stage* stages = CreateStages(map, 2, 2);

  // check the first stage
  ck_assert_int_eq(stages[0].history, HistoryEmpty);
  ck_assert_int_eq(strcmp(stages[0].tiles, map), 0);
  ck_assert_int_eq(stages[0].paths[3], 0);

  // delete stages
  DeleteStages(stages);

}
END_TEST

/*
 * Test for correct stage history.
 */
START_TEST(StagesHistoryTest)
{

  // bloody iterator
  History i;

  // create stages
  Stage* stages = CreateStages("c", 1, 1);

  // check the history
  for (i = HistoryEmpty; i < HistoryAll; ++i) {
    ck_assert_int_eq(stages[i].history, i);
  }

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
  tcase_add_test(tcase, StagesHistoryTest);

  // return the test case
  return tcase;

}
