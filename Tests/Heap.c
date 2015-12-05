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
  ck_assert_ptr_ne(heap, NULL);

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

  // return the test case
  return tcase;

}
