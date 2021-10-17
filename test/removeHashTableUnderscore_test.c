#include "lib.h"

static int indentityHashFunction(const HashTable *table, StgWord key) { return key; }

static int simpleCompare(StgWord key1, StgWord key2) { return key1 == key2; }

MunitResult test_removeHashTableUnderscore(const MunitParameter params[], void *ht) {
  StgWord key = 1;
  char value[] = "value";

  insertHashTable_(ht, key, value, indentityHashFunction);
  char *removedValue = removeHashTable_(ht, key, value, indentityHashFunction, simpleCompare);
  char *lookedUpValue = lookupHashTable_(ht, key, indentityHashFunction, simpleCompare);

  munit_assert_string_equal(value, removedValue);
  munit_assert_null(lookedUpValue);

  return MUNIT_OK;
}

MunitResult
test_removeHashTableUnderscore_twoEntriesDuplicatedKey(const MunitParameter params[],
                                             void *ht) {
  StgWord key = 1;
  char value_1[] = "value_1";
  char value_2[] = "value_2";

  insertHashTable_(ht, key, value_1, indentityHashFunction);
  insertHashTable_(ht, key, value_2, indentityHashFunction);

  char *removedValue = removeHashTable_(ht, key, value_1, indentityHashFunction, simpleCompare);
  char *lookedUpValue = lookupHashTable_(ht, key, indentityHashFunction, simpleCompare);

  munit_assert_string_equal(value_1, removedValue);

  // TODO: I think both entries should have been removed!
  // munit_assert_null(lookedUpValue);
  munit_assert_string_equal(value_2, lookedUpValue);

  return MUNIT_OK;
}

MunitTest removeHashTableUnderscore_tests[] = {
    {
        "/test_removeHashTableUnderscore", /* name */
        &test_removeHashTableUnderscore,   /* test */
        createHashTable,         /* setup */
        destroyHashTable,        /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },
    {
        "/test_removeHashTableUnderscore_twoEntriesDuplicatedKey", /* name */
        &test_removeHashTableUnderscore_twoEntriesDuplicatedKey,   /* test */
        createHashTable,                                 /* setup */
        destroyHashTable,                                /* tear_down */
        MUNIT_TEST_OPTION_NONE,                          /* options */
        NULL                                             /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
