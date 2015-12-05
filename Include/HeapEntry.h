#ifndef _HEAPENTRY_H
#define _HEAPENTRY_H

#include "Base.h"
#include "History.h"

/*
 * A single entry in the processing minimum binary heap.
 */
typedef struct HeapEntry {

  /*
   * Path length up to this tile, including the tile.
   */
  uchar path;

  /*
   * Direction to this tile.
   */
  uchar direction;

  /*
   * Stage history.
   */
  History history;

  /*
   * Tile number in the stage.
   */
  uint tile;

} HeapEntry;

#endif
