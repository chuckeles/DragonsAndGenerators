#ifndef _BASE_H
#define _BASE_H

/*
 * Base types shortcutted for better usage.
 */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

/*
 * Base defines so I don't have to include stdlib.
 */
#ifndef NULL
  #define NULL ((void*) 0)
#endif

#ifndef EXIT_SUCCESS
  #define EXIT_SUCCESS 0
  #define EXIT_FAILURE 1
#endif

#endif
