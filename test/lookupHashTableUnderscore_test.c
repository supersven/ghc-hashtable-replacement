#include "lib.h"

static int indentityHashFunction(const HashTable *table, StgWord key) { return key; }

static int simpleCompare(StgWord key1, StgWord key2) { return key1 == key2; }

MunitResult test_lookupHashTableUnderscore(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    insertHashTable_(ht, key, value, indentityHashFunction);
    char* lookedUpValue = lookupHashTable_(ht, key, indentityHashFunction, simpleCompare);

    munit_assert_string_equal(value, lookedUpValue);

    return MUNIT_OK;
}

MunitResult test_lookupHashTableUnderscore_emptyTable(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    char* lookedUpValue = lookupHashTable_(ht, key, indentityHashFunction, simpleCompare);

    munit_assert_null(lookedUpValue);

    return MUNIT_OK;
}

MunitTest lookupHashTableUnderscore_tests[] = {
  {
    "/test_lookupHashTableUnderscore", /* name */
    &test_lookupHashTableUnderscore, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_lookupHashTableUnderscore_emptyTable", /* name */
    &test_lookupHashTableUnderscore_emptyTable, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
