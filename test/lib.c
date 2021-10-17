#include "lib.h"
#include "Hash.h"

void *createHashTable(const MunitParameter params[], void *user_data) {
  return allocHashTable();
}

void destroyHashTable(void *ht) { freeHashTable(ht, NULL); }

void *createStrHashTable(const MunitParameter params[], void *user_data) {
  return allocStrHashTable();
}

void destroyStrHashTable(void *ht) { freeStrHashTable(ht, NULL); }

void *createHashSet(const MunitParameter params[], void *user_data) {
  return allocHashSet();
}

void destroyHashSet(void *ht) { freeHashSet(ht); }
