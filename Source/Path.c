#include <stdlib.h>

#include "Heap.h"
#include "Path.h"

/*
 * Definitions for path-finding functions.
 */

int* FindPath(Stage* stages, ushort width, ushort height, uint* length) {

  // create a heap
  Heap heap = CreateHeap();

  // make the first tile
  HeapEntry firstTile;
  firstTile.path = 1;
  firstTile.direction = 0;
  firstTile.history = HistoryEmpty;
  firstTile.tile = 0;

  // push it to the heap
  HeapPush(&heap, firstTile);

  // loop until we find the path or run out of tiles
  while (heap.size > 0) {
    
  }

  // delete the heap
  DeleteHeap(heap);

  return NULL;

}

void DeletePath(int* path) {

  // free the path
  free(path);

}
