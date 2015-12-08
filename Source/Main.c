/*
 * Copyright (C) Chuckeles
 *
 * For license information, check the LICENSE.md file.
 */

#include <stdlib.h>

#include "Path.h"

/*
 * Kills the dragon and finds the princesses. Keeps it sweet and short.
 * This is according to the assignment.
 */
int* zachran_princezne(char** mapa, int n, int m, int t, int* dlzka_cesty) {

  // make an array for the map
  char* mapArray = malloc(n * m  * sizeof(char));

  // copy the map
  uint i, j;
  uint princessCount = 0;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j) {
      // check if it is a princess
      if (mapa[i][j] == 'p') {
        // yep, change to pqr
        ++princessCount;

        if (princessCount > 2) {
          mapArray[i * m + j] = 'r';
          break;
        }
        else if (princessCount > 1) {
          mapArray[i * m + j] = 'q';
        }
        else {
          mapArray[i * m + j] = 'p';
        }
      }
      else {
        // nope, just copy
        mapArray[i * m + j] = mapa[i][j];
      }
    }
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
