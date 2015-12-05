#include <stdlib.h>

#include "Heap.h"

/*
 * Definitions for heap functions.
 */

Heap CreateHeap() {

  // create an empty array
  return malloc(MAX_HEAP_SIZE * sizeof(HeapEntry));

}

void DeleteHeap(Heap heap) {

  // free the heap
  free(heap);

}
