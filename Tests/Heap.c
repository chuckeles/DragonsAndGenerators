#include "Heap.h"
#include "Tests.h"

/*
 * Test for heap creation and deletion.
 */
START_TEST(HeapCreateTest)
{

  // create a heap
  Heap heap = CreateHeap();

  // check if it exists
  ck_assert_ptr_ne(heap.array, NULL);

  // delete heap
  DeleteHeap(heap);

}
END_TEST

/*
 * Test for pushing and popping items from a heap.
 */
START_TEST(HeapPushPop)
{

  // create a heap
  Heap heap = CreateHeap();

  // make an entry
  HeapEntry entry;
  entry.path = 2;
  entry.direction = 0;
  entry.history = HistoryDragon | HistoryPrincess0;
  entry.tile = 1;

  // push the entry
  HeapPush(heap, entry);

  // pop an entry
  HeapEntry entry2 = HeapPop(heap);

  // check it
  ck_assert_int_eq(entry.path, entry2.path);
  ck_assert_int_eq(entry.direction, entry2.direction);
  ck_assert_int_eq(entry.history, entry2.history);
  ck_assert_int_eq(entry.tile, entry2.tile);

  // delete heap
  DeleteHeap(heap);

}
END_TEST

/*
 * Heap test case.
 */
TCase* HeapTCase() {

  // create the test case
  TCase* tcase = tcase_create("Heap");

  // add tests
  tcase_add_test(tcase, HeapCreateTest);
  tcase_add_test(tcase, HeapPushPop);

  // return the test case
  return tcase;

}
