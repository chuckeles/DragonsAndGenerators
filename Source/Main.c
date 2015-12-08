/*
 * Copyright (C) Chuckeles
 *
 * For license information, check the LICENSE.md file.
 */

#include <stdlib.h>
#include <string.h>

#include "Path.h"

/*
 * Kills the dragon and finds the princesses. Keeps it sweet and short.
 * This is according to the assignment.
 */
int* zachran_princezne(char** mapa, int n, int m, int t, int* dlzka_cesty) {

  // make an array for the map
  char* mapArray = malloc((n * m + 1) * sizeof(char));

  // copy the map
  uint i;
  for (i = 0; i < n; ++i) {
    strcpy(mapArray + i * m, mapa[i]);
  }

  // create the stages
  Stage* stages = CreateStages(mapArray, (ushort) m, (ushort) n);

  // get the path
  int* path = FindPath(stages, (ushort) m, (ushort) n, (uint*) dlzka_cesty);

  // delete all the stuff
  DeleteStages(stages);
  free(mapArray);

  // return the result
  return path;

}
