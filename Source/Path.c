#include <stdlib.h>
#include <string.h>

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
#define PUSH_NEIGHBOUR(dir) \
  ushort tile = MAKE_1D(neighbourX, neighbourY, width); \
  char tileChar = stage->tiles[tile]; \
  \
  if (tileChar != 'n') { \
    neighbour.path = (uchar) (entry.path + (tileChar == 'h' ? 2 : 1)); \
    neighbour.direction = dir; \
    neighbour.history = entry.history; \
    neighbour.tile = tile; \
    \
    HeapPush(heap, neighbour); \
  }

/*
 * Processes a tile. Updates it and pushes the neighbours.
 */
inline void ProcessTile(Heap* heap, Stage* stage, HeapEntry entry, ushort x, ushort y, ushort width, ushort height) {

  // update the tile
  stage->paths[entry.tile] = entry.path;
  stage->directions[entry.tile] = entry.direction;

  // add neighbours to the heap
  HeapEntry neighbour;
  ushort neighbourX;
  ushort neighbourY;

  // left
  if (x > 0) {
    // set position
    neighbourX = (ushort) (x - 1);
    neighbourY = y;

    PUSH_NEIGHBOUR(0)
  }

  // up
  if (y > 0) {
    // set position
    neighbourX = x;
    neighbourY = (ushort) (y - 1);

    PUSH_NEIGHBOUR(1)
  }

  // down
  if (y < height - 1) {
    // set position
    neighbourX = x;
    neighbourY = (ushort) (y + 1);

    PUSH_NEIGHBOUR(2)
  }

  // right
  if (x < width - 1) {
    // set position
    neighbourX = (ushort) (x + 1);
    neighbourY = y;

    PUSH_NEIGHBOUR(3)
  }

}

/*
 * Creates the new stage if it doesn't exist yet.
 */
inline void EnsureStageExists(Stage* stage, Stage* newStage, ushort width, ushort height) {

  // check if it doesn't exist
  if (newStage->tiles == NULL) {
    newStage->tiles = strdup(stage->tiles);
    newStage->paths = calloc(width * height, sizeof(uchar));
    newStage->directions = malloc(width * height * sizeof(uchar));
  }

}

/*
 * Processes a tile that triggers a new stage.
 */
inline void ProcessStageTile(Stage* stages, Heap* heap, Stage* stage, HeapEntry entry,
                             ushort x, ushort y, ushort width, ushort height, History addHistory) {
  // check if already killed dragon
  if (entry.history & addHistory) {
    // just process
    ProcessTile(heap, stage, entry, x, y, width, height);
  }
  else {
    // update the tile
    stage->paths[entry.tile] = entry.path;
    stage->directions[entry.tile] = entry.direction;

    // update history
    entry.history |= addHistory;

    // get the new stage
    Stage* newStage = stages + entry.history;

    // ensure the stage exists
    EnsureStageExists(stage, newStage, width, height);

    // get tile's existing path
    uchar oldPath2 = newStage->paths[entry.tile];

    // check the existing path
    if (oldPath2 == 0 || oldPath2 > entry.path) {
      ProcessTile(heap, newStage, entry, x, y, width, height);
    }
  }
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

    // check existing path
    if (oldPath == 0 || oldPath > entry.path) {
      // get position
      ushort x = (ushort) MAKE_2D_X(entry.tile, width);
      ushort y = (ushort) MAKE_2D_Y(entry.tile, width);

      // check the tile
      switch (stage->tiles[entry.tile]) {
        case 'd':
          ProcessStageTile(stages, &heap, stage, entry, x, y, width, height, HistoryDragon);
          break;

        case 'g':
          ProcessStageTile(stages, &heap, stage, entry, x, y, width, height, HistoryGenerator);
          break;

        case 'p':
          // check if the dragon is dead
          if (entry.history & HistoryDragon) {
            ProcessStageTile(stages, &heap, stage, entry, x, y, width, height, HistoryPrincess0);
          }
          else {
            ProcessTile(&heap, stage, entry, x, y, width, height);
          }
          break;

        default:
          ProcessTile(&heap, stage, entry, x, y, width, height);
          break;
      }
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
