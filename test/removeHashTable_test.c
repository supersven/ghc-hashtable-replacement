#include "lib.h"

MunitResult test_removeHashTable(const MunitParameter params[], void *ht) {
  StgWord key = 1;
  char value[] = "value";

  insertHashTable(ht, key, value);
  char *removedValue = removeHashTable(ht, key, value);
  char *lookedUpValue = lookupHashTable(ht, key);

  munit_assert_string_equal(value, removedValue);
  munit_assert_null(lookedUpValue);

  return MUNIT_OK;
}

MunitResult
test_removeHashTable_twoEntriesDuplicatedKey(const MunitParameter params[],
                                             void *ht) {
  StgWord key = 1;
  char value_1[] = "value_1";
  char value_2[] = "value_2";

  insertHashTable(ht, key, value_1);
  insertHashTable(ht, key, value_2);

  char *removedValue = removeHashTable(ht, key, value_1);
  char *lookedUpValue = lookupHashTable(ht, key);

  munit_assert_string_equal(value_1, removedValue);

  // TODO: I think both entries should have been removed!
  // munit_assert_null(lookedUpValue);
  munit_assert_string_equal(value_2, lookedUpValue);

  return MUNIT_OK;
}

MunitTest removeHashTable_tests[] = {
    {
        "/test_removeHashTable", /* name */
        &test_removeHashTable,   /* test */
        createHashTable,         /* setup */
        destroyHashTable,        /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },
    {
        "/test_removeHashTable_twoEntriesDuplicatedKey", /* name */
        &test_removeHashTable_twoEntriesDuplicatedKey,   /* test */
        createHashTable,                                 /* setup */
        destroyHashTable,                                /* tear_down */
        MUNIT_TEST_OPTION_NONE,                          /* options */
        NULL                                             /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
