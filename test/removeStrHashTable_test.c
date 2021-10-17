#include "lib.h"

MunitResult test_removeStrHashTable(const MunitParameter params[], void *ht) {
  char* key = "key";
  char* value = "value";

  insertStrHashTable(ht, key, value);
  char *removedValue = removeStrHashTable(ht, key, value);
  char *lookedUpValue = lookupStrHashTable(ht, key);

  munit_assert_string_equal(value, removedValue);
  munit_assert_null(lookedUpValue);

  return MUNIT_OK;
}

MunitResult
test_removeStrHashTable_twoEntriesDuplicatedKey(const MunitParameter params[],
                                             void *ht) {
  char* key = "key";
  char* value_1 = "value_1";
  char* value_2 = "value_2";

  insertStrHashTable(ht, key, value_1);
  insertStrHashTable(ht, key, value_2);

  char *removedValue = removeStrHashTable(ht, key, value_1);
  char *lookedUpValue = lookupStrHashTable(ht, key);

  munit_assert_string_equal(value_1, removedValue);

  // TODO: I think both entries should have been removed!
  // munit_assert_null(lookedUpValue);
  munit_assert_string_equal(value_2, lookedUpValue);

  return MUNIT_OK;
}

MunitTest removeStrHashTable_tests[] = {
    {
        "/test_removeStrHashTable", /* name */
        &test_removeStrHashTable,   /* test */
        createHashTable,         /* setup */
        destroyHashTable,        /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },
    {
        "/test_removeStrHashTable_twoEntriesDuplicatedKey", /* name */
        &test_removeStrHashTable_twoEntriesDuplicatedKey,   /* test */
        createHashTable,                                 /* setup */
        destroyHashTable,                                /* tear_down */
        MUNIT_TEST_OPTION_NONE,                          /* options */
        NULL                                             /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
