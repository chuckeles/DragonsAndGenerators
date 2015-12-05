#ifndef _STAGE_H
#define _STAGE_H

#include "Base.h"
#include "History.h"

/*
 * A single stage represented by a map, path lengths and directions.
 */
typedef struct Stage {

  /*
   * The history of the stage.
   */
  History history;

  /*
   * The map tiles.
   */
  char* tiles;

  /*
   * Tile paths.
   */
  uchar* paths;

  /*
   * Directions to previous tile.
   */
  uchar* directions;

} Stage;

/*
 * Creates and sets up stages.
 */
Stage* CreateStages(char* map, ushort width, ushort height);

/*
 * Deletes stages.
 */
void DeleteStages(Stage* stages);

#endif
