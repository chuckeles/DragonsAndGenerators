#ifndef _PATH_H
#define _PATH_H

/*
 * Uses stages and Dijkstra's algorithm to find the shortest path.
 */
int* FindPath(Stage* stages, ushort width, ushort height);

/*
 * Deletes a path.
 */
void DeletePath(int* path);

#endif
