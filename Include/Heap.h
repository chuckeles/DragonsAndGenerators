#ifndef _HEAP_H
#define _HEAP_H

#include "HeapEntry.h"

/*
 * Maximum heap size. Defines the size of the heap array.
 */
#define MAX_HEAP_SIZE 1000

/*
 * Heap type. Just an array of entries.
 */
typedef HeapEntry* Heap;

/*
 * Creates an empty heap.
 */
Heap CreateHeap();

/*
 * Deletes a heap.
 */
void DeleteHeap(Heap heap);

#endif
