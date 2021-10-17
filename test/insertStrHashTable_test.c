#include "lib.h"

MunitResult test_insertStrHashTable_duplicatekey(const MunitParameter params[],
                                                 void *ht) {
  char *key = "key";

  insertStrHashTable(ht, key, "value_1");
  insertStrHashTable(ht, key, "value_2");
  char *lookedUpValue = lookupStrHashTable(ht, key);

  munit_assert_string_equal("value_2", lookedUpValue);

  return MUNIT_OK;
}

MunitTest insertStrHashTable_tests[] = {
    {
        "/test_insertHashTable_duplicatekey",  /* name */
        &test_insertStrHashTable_duplicatekey, /* test */
        createStrHashTable,                    /* setup */
        destroyStrHashTable,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE,                /* options */
        NULL                                   /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
