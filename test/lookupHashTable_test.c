#include "lib.h"

MunitResult test_lookupHashTable(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    insertHashTable(ht, key, value);
    char* lookedUpValue = lookupHashTable(ht, key);

    munit_assert_string_equal(value, lookedUpValue);

    return MUNIT_OK;
}

MunitResult test_lookupHashTable_emptyTable(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    char* lookedUpValue = lookupHashTable(ht, key);

    munit_assert_null(lookedUpValue);

    return MUNIT_OK;
}

MunitTest lookupHashTable_tests[] = {
  {
    "/test_lookupHashTable", /* name */
    &test_lookupHashTable, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_lookupHashTable_emptyTable", /* name */
    &test_lookupHashTable_emptyTable, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
