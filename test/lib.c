#include "lib.h"

void *createHashTable(const MunitParameter params[], void *user_data) {
  return allocHashTable();
}

void destroyHashTable(void *ht) { freeHashTable(ht, NULL); }
