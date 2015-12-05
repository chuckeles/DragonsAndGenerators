#include <stdlib.h>
#include <string.h>

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
  stages[0].tiles = strdup(map);

  // make the paths and directions
  uint size = width * height;
  stages[0].paths = malloc(size * sizeof(char));
  stages[0].directions = malloc(size * sizeof(char));

  for (i = 0; i < size; ++i) {
    stages[0].paths[i] = 0;
    stages[0].directions[i] = 0;
  }

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
