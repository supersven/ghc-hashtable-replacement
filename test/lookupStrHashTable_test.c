#include "lib.h"

MunitResult test_lookupStrHashTable(const MunitParameter params[], void* ht) {
    char* key = "key";
    char* value = "value";

    insertStrHashTable(ht, key, value);
    char* lookedUpValue = lookupStrHashTable(ht, key);

    munit_assert_string_equal(value, lookedUpValue);

    return MUNIT_OK;
}

MunitResult test_lookupStrHashTable_emptyTable(const MunitParameter params[], void* ht) {
    char* key = "key";
    char* value = "value";

    char* lookedUpValue = lookupStrHashTable(ht, key);

    munit_assert_null(lookedUpValue);

    return MUNIT_OK;
}

MunitTest lookupStrHashTable_tests[] = {
  {
    "/test_lookupStrHashTable", /* name */
    &test_lookupStrHashTable, /* test */
    createStrHashTable, /* setup */
    destroyStrHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_lookupStrHashTable_emptyTable", /* name */
    &test_lookupStrHashTable_emptyTable, /* test */
    createStrHashTable, /* setup */
    destroyStrHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
