#ifndef _PATH_H
#define _PATH_H

#include "Base.h"
#include "Stage.h"

/*
 * Uses stages and Dijkstra's algorithm to find the shortest path.
 */
int* FindPath(Stage* stages, ushort width, ushort height, uint* length);

/*
 * Deletes a path.
 */
void DeletePath(int* path);

#endif
