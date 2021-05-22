#include "FakedRtsIncludes.h"
#include <stdlib.h>
#include <string.h>

void *
stgMallocBytes (size_t n, char *msg)
{
    void *space;

    if ((space = malloc(n)) == NULL) {
      /* Quoting POSIX.1-2008 (which says more or less the same as ISO C99):
       *
       *   "Upon successful completion with size not equal to 0, malloc() shall
       *   return a pointer to the allocated space. If size is 0, either a null
       *   pointer or a unique pointer that can be successfully passed to free()
       *   shall be returned. Otherwise, it shall return a null pointer and set
       *   errno to indicate the error."
       *
       * Consequently, a NULL pointer being returned by `malloc()` for a 0-size
       * allocation is *not* to be considered an error.
       */
      if (n == 0) return NULL;

      /* don't fflush(stdout); WORKAROUND bug in Linux glibc */
      // rtsConfig.mallocFailHook((W_) n, msg);
      stg_exit(EXIT_INTERNAL_ERROR);
    }
    IF_DEBUG(zero_on_gc, memset(space, 0xbb, n));
    return space;
}

/* To simplify changing the underlying allocator used
 * by stgMallocBytes(), provide stgFree() as well.
 */
void
stgFree(void* p)
{
  free(p);
}
