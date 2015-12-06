#ifndef _HISTORY_H
#define _HISTORY_H

/*
 * A history of a particular stage. What the player has been through up to this point.
 */
typedef enum History {

  HistoryEmpty = 0,

  HistoryDragon = 1,
  HistoryGenerator = 2,
  HistoryPrincess0 = 4,
  HistoryPrincess1 = 8,
  HistoryPrincess2 = 16,

  HistoryAll = 31,

  HistoryFinish = HistoryPrincess0 | HistoryPrincess1 | HistoryPrincess2

} History;

#endif
