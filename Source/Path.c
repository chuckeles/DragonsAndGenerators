#include <stdlib.h>
#include <stdio.h>

#include "Heap.h"
#include "Path.h"

/*
 * Utility macros for converting between 1D and 2D.
 */
#define MAKE_1D(x, y, width) (x + y * width)
#define MAKE_2D_X(i, width) (i % width)
#define MAKE_2D_Y(i, width) (i / width)

/*
 * Helpful and weird macro for adding neighbours to avoid duplicate code.
 */
#define PUSH_NEIGHBOUR \
  // check if it is not an obstacle \
  ushort tile = MAKE_1D(neighbourX, neighbourY, width); \
  char tileChar = stage->tiles[tile]; \
  if (tileChar != 'n') { \
    // set the entry \
    neighbour. \
    path = (uchar) (entry.path + (tileChar == 'h' ? 2 : 1)); \
    neighbour. \
    direction = 0; \
    neighbour. \
    history = entry.history; \
    neighbour. \
    tile = tile; \
    \
    // add to the heap \
    HeapPush(&heap, neighbour); \
  }

/*
 * Definitions for path-finding functions.
 */

int* FindPath(Stage* stages, ushort width, ushort height, uint* length) {

  // create a heap
  Heap heap = CreateHeap();

  // make the first tile
  HeapEntry firstTile;
  firstTile.path = (uchar) (stages[HistoryEmpty].tiles[0] == 'h' ? 2 : 1);
  firstTile.direction = 0;
  firstTile.history = HistoryEmpty;
  firstTile.tile = 0;

  // push it to the heap
  HeapPush(&heap, firstTile);

  // loop until we find the path or run out of tiles
  while (heap.size > 0) {
    // get the next tile
    HeapEntry entry = HeapPop(&heap);

    // get the stage
    Stage* stage = stages + entry.history;

    // get tile's existing path
    uchar oldPath = stage->paths[entry.tile];

    // get position
    ushort x = (ushort) MAKE_2D_X(entry.tile, width);
    ushort y = (ushort) MAKE_2D_Y(entry.tile, width);

    // DEBUG
    printf("Processing tile: %c\n", stage->tiles[entry.tile]);

    // check the tile
    switch (stage->tiles[entry.tile]) {
      default:
        // DEBUG
        printf("Default processing\n");

        // check existing path
        if (oldPath == 0 || oldPath > entry.path) {
          // DEBUG
          printf("Updating tile\n");

          // update the tile
          stage->paths[entry.tile] = entry.path;
          stage->directions[entry.tile] = entry.direction;

          // add neighbours to the heap
          HeapEntry neighbour;
          ushort neighbourX;
          ushort neighbourY;

          // left
          if (x > 0) {
            // DEBUG
            printf("Adding left neighbour\n");

            // set position
            neighbourX = (ushort) (x - 1);
            neighbourY = y;

            PUSH_NEIGHBOUR
          }

          // up
          if (y > 0) {
            // DEBUG
            printf("Adding up neighbour\n");

            // set position
            neighbourX = x;
            neighbourY = (ushort) (y - 1);

            PUSH_NEIGHBOUR
          }

          // down
          if (y < height - 1) {
            // DEBUG
            printf("Adding down neighbour\n");

            // set position
            neighbourX = x;
            neighbourY = (ushort) (y + 1);

            PUSH_NEIGHBOUR
          }

          // right
          if (x < width - 1) {
            // DEBUG
            printf("Adding right neighbour\n");

            // set position
            neighbourX = (ushort) (x + 1);
            neighbourY = y;

            PUSH_NEIGHBOUR
          }
        }

        break;
    }
  }

  // delete the heap
  DeleteHeap(heap);

  return NULL;

}

void DeletePath(int* path) {

  // free the path
  free(path);

}
