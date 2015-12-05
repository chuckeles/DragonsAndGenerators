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
  ck_assert_int_ne(heap.array, NULL);

  // delete heap
  DeleteHeap(heap);

}
END_TEST

/*
 * Test for pushing and popping items from a heap.
 */
START_TEST(HeapPushPopTest)
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
  HeapPush(&heap, entry);

  // check size
  ck_assert_int_eq(heap.size, 1);

  // pop an entry
  HeapEntry entry2 = HeapPop(&heap);

  // check size
  ck_assert_int_eq(heap.size, 0);

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
 * Test for working minimum binary heap.
 */
START_TEST(HeapMinTest)
{

  // create a heap
  Heap heap = CreateHeap();

  // make entries
  HeapEntry entry1;
  HeapEntry entry2;
  HeapEntry entry3;
  HeapEntry entry4;

  entry1.path = 5;
  entry2.path = 8;
  entry3.path = 4;
  entry4.path = 5;

  entry1.direction = 1;
  entry4.direction = 3;

  // push them
  HeapPush(&heap, entry1);
  HeapPush(&heap, entry2);
  HeapPush(&heap, entry3);
  HeapPush(&heap, entry4);

  // check size
  ck_assert_int_eq(heap.size, 4);

  // pop and check
  ck_assert_int_eq(HeapPop(&heap).path, 4);
  HeapEntry popEntry2 = HeapPop(&heap);
  HeapEntry popEntry3 = HeapPop(&heap);
  ck_assert_int_eq(HeapPop(&heap).path, 8);

  ck_assert_int_eq(popEntry2.path, 5);
  ck_assert_int_eq(popEntry3.path, 5);
  ck_assert_int_eq(popEntry2.direction, 1);
  ck_assert_int_eq(popEntry3.direction, 3);

  // check size
  ck_assert_int_eq(heap.size, 0);

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
  tcase_add_test(tcase, HeapPushPopTest);
  tcase_add_test(tcase, HeapMinTest);

  // return the test case
  return tcase;

}
