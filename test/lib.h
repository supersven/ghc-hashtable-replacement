#include <FakedRtsIncludes.h>
#include <Hash.h>
#include "munit/munit.h"

void *createHashTable(const MunitParameter params[], void *user_data);
void destroyHashTable(void *ht);

void *createStrHashTable(const MunitParameter params[], void *user_data);
void destroyStrHashTable(void *ht);

void *createHashSet(const MunitParameter params[], void *user_data);
void destroyHashSet(void *ht);
