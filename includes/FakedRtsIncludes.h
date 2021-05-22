#pragma once

// For NULL
#include "stddef.h"
//For bool
#include <stdbool.h>

// Types.h
#include <inttypes.h>
typedef uint64_t           StgWord;

// Stg.h
#define GNUC3_ATTRIBUTE(at) __attribute__((at))
#define GNU_ATTRIBUTE(at) __attribute__((at))

#define INLINE_HEADER static inline
#define STATIC_INLINE static inline

typedef StgWord      W_;

// RtsUtils.h
void *stgMallocBytes(size_t n, char *msg)
    GNUC3_ATTRIBUTE(__malloc__);

void stgFree(void* p);

void stg_exit(int n) GNU_ATTRIBUTE(__noreturn__);


// Rts.h
#define doNothing() do { } while (0)

/* -----------------------------------------------------------------------------
   Assertions and Debuggery

   CHECK(p)   evaluates p and terminates with an error if p is false
   ASSERT(p)  like CHECK(p) if DEBUG is on, otherwise a no-op
   -------------------------------------------------------------------------- */

void _assertFail(const char *filename, unsigned int linenum)
   GNUC3_ATTRIBUTE(__noreturn__);

#define CHECK(predicate)                        \
        if (RTS_LIKELY(predicate))              \
            /*null*/;                           \
        else                                    \
            _assertFail(__FILE__, __LINE__)

#define CHECKM(predicate, msg, ...)             \
        if (RTS_LIKELY(predicate))              \
            /*null*/;                           \
        else                                    \
            barf(msg, ##__VA_ARGS__)

#if !defined(DEBUG)
#define ASSERT(predicate) /* nothing */
#define ASSERTM(predicate,msg,...) /* nothing */
#else
#define ASSERT(predicate) CHECK(predicate)
#define ASSERTM(predicate,msg,...) CHECKM(predicate,msg,##__VA_ARGS__)
#endif /* DEBUG */

/* -----------------------------------------------------------------------------
   Assertions and Debuggery
   -------------------------------------------------------------------------- */

#define IF_RTSFLAGS(c,s)  if (RtsFlags.c) { s; } doNothing()

#if defined(DEBUG)
/* See Note [RtsFlags is a pointer in STG code] */
#if IN_STG_CODE
#define IF_DEBUG(c,s)  if (RtsFlags[0].DebugFlags.c) { s; } doNothing()
#else
#define IF_DEBUG(c,s)  if (RtsFlags.DebugFlags.c) { s; } doNothing()
#endif /* IN_STG_CODE */
#else
#define IF_DEBUG(c,s)  doNothing()
#endif /* DEBUG */

#if defined(DEBUG)
#define DEBUG_ONLY(s) s
#else
#define DEBUG_ONLY(s) doNothing()
#endif /* DEBUG */

#if defined(DEBUG)
#define DEBUG_IS_ON   1
#else
#define DEBUG_IS_ON   0
#endif /* DEBUG */

/* -----------------------------------------------------------------------------
   RTS Exit codes
   -------------------------------------------------------------------------- */

/* 255 is allegedly used by dynamic linkers to report linking failure */
#define EXIT_INTERNAL_ERROR 254
#define EXIT_DEADLOCK       253
#define EXIT_INTERRUPTED    252
#define EXIT_HEAPOVERFLOW   251
#define EXIT_KILLED         250
