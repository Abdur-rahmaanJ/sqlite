/* This demonstration code is part of the SQLite forum thread
 *
 *  "Proposal and code: Superset of SQLite Debugging"
 *
 * and contains the code for new compile-time debugging facilities, and 
 * some no-op illustrations.
 *
 * Compile sqlitedebug (this file) with $CC parameters as follows, then
 * run it:
 *
 * gcc -Wall -O2 sqlitedebug.c -o sqlitedebug -D [...]
 *
 * where example -D options are:
 * 
 *   -D SQLITE_DEBUG
 *   -D SQLITE_SELECTIVE_DEBUG -DDEBUG_LEVEL=1
 *   -D SQLITE_SELECTIVE_DEBUG -DDEBUG_ALL
 *   -D SQLITE_SELECTIVE_DEBUG -DDEBUG_VIRTUAL_MACHINE -DDEBUG_STORAGE
 *   -D SQLITE_SELECTIVE_DEBUG -DDEBUG_LEVEL=2 -DDEBUG_VIRTUAL_MACHINE
 *
 * There are many other combinations, but this gives the idea of how levels
 * and categories of debugging works, and that SQLITE_DEBUG works unchanged.
 *
 * Dan Shearer
 * dan@shearer.org
 * 2020-09-22
*/

#include <stdlib.h>
#include <stdio.h>


/* Levels of Debugging Info, currently 3 levels 1-3
 *
 * Level 3 is the default, and applies if DEBUG_LEVEL is undefined
 *
 *
 * Level 1      status labels, such as "Flag status in Opcode XX is %s". Also
 *              useful for ad-hoc debugging 
 * Level 2      Level 1 plus flow labels, such as notification of 
                "Entering/Leaving Function X"
 * Level 3      Level 2 plus data structure dumps, and anything else
*/


#if defined(SQLITE_SELECTIVE_DEBUG)
	#define SELECTIVE_DEBUG(l) DEBUG_ALL || (l)

	#if !defined(DEBUG_LEVEL) /* default to 3 */
	#define DEBUG_LEVEL 3
	#endif

	#if (DEBUG_LEVEL < 1) || (DEBUG_LEVEL > 3)
	#error "DEBUG_LEVEL must be between 1 and 3. Default is 3"
	#endif
#else
	#define SELECTIVE_DEBUG(l) 0

	#if defined(DEBUG_ALL)
	#error "DEBUG_ALL specified without SQLITE_SELECTIVE_DEBUG"
	#endif

	#if defined(DEBUG_LEVEL)
	#error "DEBUG_LEVEL specified without SQLITE_SELECTIVE_DEBUG"
	#endif

#endif /* SELECTIVE_DEBUG */

#if defined(SQLITE_SELECTIVE_DEBUG)

	#define DEBUG_PRINT(level,x) \
		if (level <= DEBUG_LEVEL) { \
	       		printf("Level: %d file:%s line:%d %s\n",level,__FILE__,__LINE__,x); \
		}
		
#else
	#define DEBUG_PRINT(level,x) do {} while (0)
#endif
