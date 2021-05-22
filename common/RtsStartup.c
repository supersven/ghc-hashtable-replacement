#include <stdlib.h>

/*
 * called from STG-land to exit the program
 */

void (*exitFn)(int) = 0;

void
stg_exit(int n)
{
  if (exitFn)
    (*exitFn)(n);
  exit(n);
}
