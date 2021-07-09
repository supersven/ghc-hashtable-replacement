#include "lib.h"
#include <stddef.h>

MunitResult test_keysHashTable(const MunitParameter params[], void *ht) {
  StgWord key = 1;
  char value[] = "value";

  insertHashTable(ht, key, value);

  StgWord *buf = munit_new(StgWord);
  int count = keysHashTable(ht, buf, 1);

  munit_assert_uint64(buf[0], ==, 1);
  munit_assert_int(count, ==, 1);

  return MUNIT_OK;
}

MunitResult test_keysHashTable_emptyArray(const MunitParameter params[],
                                          void *ht) {
  StgWord key = 1;
  char value[] = "value";

  insertHashTable(ht, key, value);

  StgWord *buf = munit_new(StgWord);
  int count = keysHashTable(ht, buf, 0);

  munit_assert_uint64(buf[0], ==, 0);
  munit_assert_int(count, ==, 0);

  return MUNIT_OK;
}

MunitResult test_keysHashTable_emptyTable(const MunitParameter params[],
                                          void *ht) {
  StgWord *buf = munit_new(StgWord);
  int count = keysHashTable(ht, buf, 0);

  munit_assert_uint64(buf[0], ==, 0);
  munit_assert_int(count, ==, 0);

  return MUNIT_OK;
}

MunitTest keysHashTable_tests[] = {
    {
        "/test_keysHashTable",  /* name */
        &test_keysHashTable,    /* test */
        createHashTable,        /* setup */
        destroyHashTable,       /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/test_keysHashTable_emptyArray", /* name */
        &test_keysHashTable_emptyArray,   /* test */
        createHashTable,                  /* setup */
        destroyHashTable,                 /* tear_down */
        MUNIT_TEST_OPTION_NONE,           /* options */
        NULL                              /* parameters */
    },
    {
        "/test_keysHashTable_emptyTable", /* name */
        &test_keysHashTable_emptyTable,   /* test */
        createHashTable,                  /* setup */
        destroyHashTable,                 /* tear_down */
        MUNIT_TEST_OPTION_NONE,           /* options */
        NULL                              /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
    };
