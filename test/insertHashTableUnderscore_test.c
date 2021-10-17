#include "lib.h"

static int simpleCompare(StgWord key1, StgWord key2) { return key1 == key2; }

MunitResult
test_insertHashTableUnderscore_duplicatekey(const MunitParameter params[],
                                            void *ht) {
  StgWord key = 1;

  insertHashTable_(ht, key, "value_1", hashWord);
  insertHashTable_(ht, key, "value_2", hashWord);
  char *lookedUpValue = lookupHashTable_(ht, key, hashWord, simpleCompare);

  munit_assert_not_null(lookedUpValue);
  munit_assert_string_equal("value_2", lookedUpValue);

  return MUNIT_OK;
}

static int indentityHashFunction(const HashTable *table, StgWord key) { return key; }

MunitResult test_insertHashTableUnderscore_duplicatekey_indentityHashFunction(
    const MunitParameter params[], void *ht) {
  StgWord key = 1;

  insertHashTable_(ht, key, "value_1", indentityHashFunction);
  insertHashTable_(ht, key, "value_2", indentityHashFunction);
  char *lookedUpValue =
      lookupHashTable_(ht, key, indentityHashFunction, simpleCompare);

  munit_assert_not_null(lookedUpValue);
  munit_assert_string_equal("value_2", lookedUpValue);

  return MUNIT_OK;
}

MunitTest insertHashTableUnderscore_tests[] = {
    {
        "/test_insertHashTableUnderscore_duplicatekey", /* name */
        &test_insertHashTableUnderscore_duplicatekey,   /* test */
        createHashTable,                                /* setup */
        destroyHashTable,                               /* tear_down */
        MUNIT_TEST_OPTION_NONE,                         /* options */
        NULL                                            /* parameters */
    },
    {
        "/test_insertHashTableUnderscore_duplicatekey_indentityHashFunction", /* name */
        &test_insertHashTableUnderscore_duplicatekey_indentityHashFunction,   /* test */
        createHashTable,                                /* setup */
        destroyHashTable,                               /* tear_down */
        MUNIT_TEST_OPTION_NONE,                         /* options */
        NULL                                            /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
