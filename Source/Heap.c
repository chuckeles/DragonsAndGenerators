#include <stdlib.h>
#include <stdio.h>

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

void HeapPush(Heap* heap, HeapEntry entry) {

  // save the new index
  uint index = heap->size;

  // insert to the end
  heap->array[heap->size++] = entry;

  // swap until it's a min heap again
  while (index != 0 && CompareEntries(heap->array[PARENT(index)], entry) > 0) { // order.priority > gHeap[Parent(index)].priority) {
    // swap them
    heap->array[index] = heap->array[PARENT(index)];
    heap->array[PARENT(index)] = entry;
    index = PARENT(index);
  }

}

HeapEntry HeapPop(Heap* heap) {

  // extract the root
  HeapEntry result = heap->array[0];

  // decrease size
  --heap->size;

  // return the result
  return result;

}
