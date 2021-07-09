#include "lib.h"

MunitResult test_insertHashTable_duplicatekey(const MunitParameter params[],
                                              void *ht) {
  StgWord key = 1;

  insertHashTable(ht, key, "value_1");
  insertHashTable(ht, key, "value_2");
  char *lookedUpValue = lookupHashTable(ht, key);

  munit_assert_string_equal("value_2", lookedUpValue);

  return MUNIT_OK;
}

MunitTest insertHashTable_tests[] = {
    {
        "/test_insertHashTable_duplicatekey", /* name */
        &test_insertHashTable_duplicatekey,   /* test */
        createHashTable,                      /* setup */
        destroyHashTable,                     /* tear_down */
        MUNIT_TEST_OPTION_NONE,               /* options */
        NULL                                  /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
