#include <stdlib.h>

#include "Heap.h"

/*
 * Helpful macros for getting children and parent.
 */
#define PARENT(i) ((i + 1) / 2 - 1)
#define LEFT(i) ((i + 1) * 2 - 1)
#define RIGHT(i) ((i + 1) * 2)

/*
 * Compares 2 entries. Returns 0 if equal, 1 if entry1 is larger than entry2 and -1 otherwise.
 */
int CompareEntries(HeapEntry entry1, HeapEntry entry2) {

  // check if paths are equal
  if (entry1.path == entry2.path) {
    // check the directions
    if (entry1.direction == entry2.direction) {
      // equal
      return 0;
    }
    else {
      // compare based on directions
      return entry1.direction > entry2.direction ? 1 : -1;
    }
  }

  // compare based on paths
  return entry1.path > entry2.path ? 1 : -1;

}

/*
 * Definitions for heap functions.
 */

Heap CreateHeap() {

  // make a heap
  Heap heap;

  // allocate the array
  heap.array = malloc(MAX_HEAP_SIZE * sizeof(HeapEntry));

  // initialize the size
  heap.size = 0;

  // return the heap
  return heap;

}

void DeleteHeap(Heap heap) {

  // free the heap
  free(heap.array);

}

void HeapPush(Heap heap, HeapEntry entry) {

  // save the new index
  uint index = heap.size;

  // insert to the end
  heap.array[heap.size++] = entry;

  // swap until it's a min heap again
  while (index != 0 && CompareEntries(heap.array[PARENT(index)], entry) > 0) { // order.priority > gHeap[Parent(index)].priority) {
    // swap them
    heap.array[index] = heap.array[PARENT(index)];
    heap.array[PARENT(index)] = entry;
    index = PARENT(index);
  }

}

HeapEntry HeapPop(Heap heap) {

  // extract the root
  HeapEntry result = heap.array[0];

  // extract R
  uint Ri = 0;
  HeapEntry R = heap.array[0];

  // extract P
  HeapEntry P = heap.array[--heap.size];

  // move stuff around
  /*while (P.priority < R.priority && (Left(Ri) < heap.arraySize || Right(Ri) < heap.arraySize)) {
    // the children
    HeapEntry left;
    HeapEntry right;

    // set maximum priority
    left.priority = INT_MIN;
    right.priority = INT_MIN;

    // get them
    if (Left(Ri) < heap.arraySize)
      left = heap.array[Left(Ri)];
    if (Right(Ri) < heap.arraySize)
      right = heap.array[Right(Ri)];

    // get the smaller one
    if (left.priority > right.priority) {
      if (left.priority > P.priority) {
        // move the left child
        heap.array[Ri] = left;
        Ri = Left(Ri);
      }
      R = left;
    }
    else {
      if (right.priority > P.priority) {
        // move the right child
        heap.array[Ri] = right;
        Ri = Right(Ri);
      }
      R = right;
    }
  }*/

  // place P
  heap.array[Ri] = P;

  // return the result
  return result;

}
