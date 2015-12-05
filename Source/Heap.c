#include <stdlib.h>

#include "Heap.h"

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

}

HeapEntry HeapPop(Heap heap) {

  HeapEntry e;
  return e;

}
