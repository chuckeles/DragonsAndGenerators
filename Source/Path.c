#include <stdlib.h>

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
 * Another weird macro to prevent code duplication/
 */
#define PROCESS_PRINCESS(hist) \
  if (entry.history & HistoryDragon) { \
    if (ProcessStageTile(stages, &heap, stage, entry, x, y, width, height, hist)) { \
      finish = 1; \
    } \
  } \
  else { \
    ProcessTile(&heap, stage, entry, x, y, width, height); \
  }

/*
 * And another for clearing bits in history.
 */
#define CLEAR_BIT(entry, hist) \
  if (entry.history & hist && stages[entry.history & ~hist].tiles != NULL && \
      stages[entry.history].paths[entry.tile] == stages[entry.history & ~hist].paths[entry.tile] && \
      stages[entry.history].directions[entry.tile] == stages[entry.history & ~hist].directions[entry.tile]) { \
    entry.history &= ~hist;\
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
    newStage->tiles = stage->tiles;
    newStage->paths = calloc(width * height, sizeof(uchar));
    newStage->directions = malloc(width * height * sizeof(uchar));
  }

}

/*
 * Processes a tile that triggers a new stage.
 */
inline ushort ProcessStageTile(Stage* stages, Heap* heap, Stage* stage, HeapEntry entry,
                             ushort x, ushort y, ushort width, ushort height, History addHistory) {
  // check if the result is the finish
  if (((entry.history | addHistory) & HistoryFinish) == HistoryFinish) {
    // update the tile
    stage->paths[entry.tile] = entry.path;
    stage->directions[entry.tile] = entry.direction;

    // done!
    return 1;
  }

  // check if already on the required stage
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

  return 0;

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

  // whether the finish has already been found
  ushort finish = 0;
  HeapEntry finishEntry;
  finishEntry.history = HistoryEmpty;

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
          PROCESS_PRINCESS(HistoryPrincess0)
          break;
        case 'q':
          PROCESS_PRINCESS(HistoryPrincess1)
          break;
        case 'r':
          PROCESS_PRINCESS(HistoryPrincess2)
          break;

        default:
          ProcessTile(&heap, stage, entry, x, y, width, height);
          break;
      }

      // found all princesses?
      if (finish) {
        // stop the search
        finishEntry = entry;
        break;
      }
    }
  }

  // delete the heap
  DeleteHeap(heap);

  // if finished
  if (finish) {
    // make an array for the path
    int* result = malloc(finishEntry.path * 2 * sizeof(int));

    // reset length
    *length = 0;

    // position for later
    ushort x;
    ushort y;

    // iterate tiles and add them to the array
    while (finishEntry.history != HistoryEmpty || finishEntry.tile > 0) {
      // check if we need to change the stage
      switch (stages[finishEntry.history].tiles[finishEntry.tile]) {
        case 'd':
          CLEAR_BIT(finishEntry, HistoryDragon)
          break;

        case 'g':
          CLEAR_BIT(finishEntry, HistoryGenerator)
          break;

        case 'p':
          CLEAR_BIT(finishEntry, HistoryPrincess0)
          break;
        case 'q':
          CLEAR_BIT(finishEntry, HistoryPrincess1)
          break;
        case 'r':
          CLEAR_BIT(finishEntry, HistoryPrincess2)
          break;

        // CLion... this is useless...
        default:break;
      }

      // add the position
      result[(*length)++] = MAKE_2D_Y(finishEntry.tile, width);
      result[(*length)++] = MAKE_2D_X(finishEntry.tile, width);

      // weird trick if the [0, 0] changes the stage
      if (finishEntry.history == HistoryEmpty && finishEntry.tile == 0) {
        break;
      }

      // move to the next tile
      switch (finishEntry.direction) {
        case 0:
          x = (ushort) (MAKE_2D_X(finishEntry.tile, width) + 1);
          y = (ushort) MAKE_2D_Y(finishEntry.tile, width);
          finishEntry.tile = MAKE_1D(x, y, width);
          finishEntry.direction = stages[finishEntry.history].directions[finishEntry.tile];
          break;

        case 1:
          x = (ushort) MAKE_2D_X(finishEntry.tile, width);
          y = (ushort) (MAKE_2D_Y(finishEntry.tile, width) + 1);
          finishEntry.tile = MAKE_1D(x, y, width);
          finishEntry.direction = stages[finishEntry.history].directions[finishEntry.tile];
          break;

        case 2:
          x = (ushort) MAKE_2D_X(finishEntry.tile, width);
          y = (ushort) (MAKE_2D_Y(finishEntry.tile, width) - 1);
          finishEntry.tile = MAKE_1D(x, y, width);
          finishEntry.direction = stages[finishEntry.history].directions[finishEntry.tile];
          break;

        case 3:
          x = (ushort) (MAKE_2D_X(finishEntry.tile, width) - 1);
          y = (ushort) MAKE_2D_Y(finishEntry.tile, width);
          finishEntry.tile = MAKE_1D(x, y, width);
          finishEntry.direction = stages[finishEntry.history].directions[finishEntry.tile];
          break;

        // CLion... this is useless...
        default:break;
      }
    }

    // add the [0, 0] position if not already there
    if (result[(*length) - 1] != 0 || result[(*length) - 2] != 0) {
      result[(*length)++] = 0;
      result[(*length)++] = 0;
    }

    // flip the array
    uint i;
    for (i = 0; i < (*length) / 2; ++i) {
      result[i] ^= result[(*length) - i - 1];
      result[(*length) - i - 1] ^= result[i];
      result[i] ^= result[(*length) - i - 1];
    }

    // 2 coords for 1 tile
    *length /= 2;

    // return the result
    return result;
  }

  return NULL;

}

void DeletePath(int* path) {

  // free the path
  free(path);

}
