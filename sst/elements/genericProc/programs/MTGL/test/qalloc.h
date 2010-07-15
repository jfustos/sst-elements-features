/*  _________________________________________________________________________
 *
 *  MTGL: The MultiThreaded Graph Library
 *  Copyright (c) 2008 Sandia Corporation.
 *  This software is distributed under the BSD License.
 *  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
 *  the U.S. Government retains certain rights in this software.
 *  For more information, see the README file in the top MTGL directory.
 *  _________________________________________________________________________
 */

/****************************************************************************/
/*! \file qalloc.h

    \author Jon Berry (jberry@sandia.gov)

    \date 12/4/2007
*/
/****************************************************************************/

#ifndef MTGL_QALLOC_H
#define MTGL_QALLOC_H

#define _FILE_OFFSET_BITS 64

#include <sys/types.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mapinfo_s;
struct dynmapinfo_s;

/* There are two kinds of maps: dynamic maps and static maps. Static maps have
 * very low overhead, but have the restriction that all allocations in them
 * have the same size (also, they're slower to create, initially). Dynamic maps
 * allow you to decide how much memory to use for each allocation at runtime,
 * but have more overhead both in terms of space and time (also, they're very
 * fast to create, initially). */

/* The following functions are fairly straightforward. If the file specified
 * does not exist, it will be created. If the file specified does exist, it
 * will be loaded up. */
void* qalloc_makestatmap(const off_t filesize, void* addr,
                         const char* filename, size_t itemsize,
                         const size_t streams);
void* qalloc_makedynmap(const off_t filesize, void* addr,
                        const char* filename, const size_t streams);

/* This function is a special version of the previous two. It reads the map's
 * headers to determine it's vital details, and then loads it up as if you'd
 * used the appropriate function (between the previous two). */
void* qalloc_loadmap(const char* filename);

/* This function sync's the mmap'd regions to disk. */
void qalloc_checkpoint();

/* This function performs a checkpoint, and then un-maps all of the currently
 * mapped regions */
void qalloc_cleanup();

/* These are the allocation functions.
 *
 * The statmalloc() function allocates one chunk of the size of memory
 * associated with the specified static-size map.
 * The dynmalloc() function allocates one chunk of at least "size" bytes from
 * the specified dynamic-size map.
 * The malloc() function merges the previous two; if the specified map is a
 * static-size map, the size argument is ignored.
 */
void* qalloc_statmalloc(struct mapinfo_s* map);
void* qalloc_dynmalloc(struct dynmapinfo_s* map, size_t size);
void* qalloc_malloc(void* map, size_t size);

/* These are the deallocation functions.
 *
 * The statfree() function returns a static-size chunk to its map.
 * The dynfree() function returns a dynamic-size chunk to its map.
 * The free() function is a merging of the above two.
 */
void qalloc_statfree(void* block, struct mapinfo_s* map);
void qalloc_dynfree(void* block, struct dynmapinfo_s* map);
void qalloc_free(void* block, void* map);

#ifdef __cplusplus
}
#endif

#endif
