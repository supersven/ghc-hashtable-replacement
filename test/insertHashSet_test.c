#include "lib.h"

MunitResult test_insertHashSet(const MunitParameter params[], void *ht) {
  StgWord key = 1;

  insertHashSet(ht, key);

  char *lookedUpValue = lookupHashTable(ht, key);

  munit_assert_null(lookedUpValue);
  munit_assert_int(keyCountHashTable(ht), ==, 1);

  return MUNIT_OK;
}

MunitTest insertHashSet_tests[] = {
    {
        "/test_insertHashSet",  /* name */
        &test_insertHashSet,    /* test */
        createHashSet,          /* setup */
        destroyHashSet,         /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
