#ifndef _HISTORY_H
#define _HISTORY_H

/*
 * A history of a particular stage. What the player has been through up to this point.
 */
typedef enum History {

  Empty = 0,

  Dragon = 1,
  Generator = 2,
  Princess0 = 4,
  Princess1 = 8,
  Princess2 = 16,

  All = 31

} History;

#endif
