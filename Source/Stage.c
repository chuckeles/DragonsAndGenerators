#include <stdlib.h>

#include "History.h"
#include "Stage.h"

/*
 * Definitions for stage functions.
 */

Stage* CreateStages(char* map, ushort width, ushort height) {

  // bloody iterator
  uint i;

  // allocate the stage array
  Stage* stages = calloc(HistoryAll - 1, sizeof(Stage));

  // initialize the first stage's tiles
  stages[0].tiles = map;

  // make the paths and directions
  stages[0].paths = calloc(width * height, sizeof(uchar));
  stages[0].directions = malloc(width * height * sizeof(uchar));

  // initialize history
  for (i = HistoryEmpty; i < HistoryAll; ++i) {
    stages[i].history = (History) i;
  }

  // return the stages
  return stages;

}

void DeleteStages(Stage* stages) {

  // free the array
  free(stages);

}
