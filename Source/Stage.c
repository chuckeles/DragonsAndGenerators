#include <stdlib.h>

#include "History.h"
#include "Stage.h"

/*
 * Definitions for stage functions.
 */

Stage* CreateStages(char* map, ushort width, ushort height) {

  // allocate the stage array
  return calloc(HistoryAll - 1, sizeof(Stage));

}

void DeleteStages(Stage* stages) {

  // free the array
  free(stages);

}
