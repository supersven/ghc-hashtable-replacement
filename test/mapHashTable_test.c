#include "lib.h"

typedef struct KeyValue_ {
  StgWord key;
  char *value;
} KeyValue;

void testMapHashFn(void *data, StgWord key, const void *value) {
  KeyValue **visitedEntries = (KeyValue **)data;

  for (int i = 0; i < 3; i++) {
    if (visitedEntries[i] == NULL) {
      KeyValue *kv = munit_new(KeyValue);
      kv->key = key;
      kv->value = (char *)value;
      visitedEntries[i] = kv;

      break;
    }
  }
}

MunitResult test_mapHashTable_zeroEntries(const MunitParameter params[],
                                          void *ht) {
  StgWord key = 1;
  char value[] = "value";

  KeyValue *visitedEntries[3] = {NULL, NULL, NULL};

  mapHashTable(ht, visitedEntries, testMapHashFn);

  munit_assert_null(visitedEntries[0]);
  munit_assert_null(visitedEntries[1]);
  munit_assert_null(visitedEntries[2]);

  return MUNIT_OK;
}

MunitResult test_mapHashTable_oneEntry(const MunitParameter params[],
                                       void *ht) {
  StgWord key = 1;
  char value[] = "value";

  KeyValue *visitedEntries[3] = {NULL, NULL, NULL};

  insertHashTable(ht, key, value);

  mapHashTable(ht, visitedEntries, testMapHashFn);

  munit_assert_string_equal(value, visitedEntries[0]->value);
  munit_assert_uint64(key, ==, visitedEntries[0]->key);
  munit_assert_null(visitedEntries[1]);
  munit_assert_null(visitedEntries[2]);

  free(visitedEntries[0]);
  return MUNIT_OK;
}

MunitResult test_mapHashTable_oneDuplicatedEntry(const MunitParameter params[],
                                                 void *ht) {
  StgWord key = 1;
  char value_1[] = "value_1";
  char value_2[] = "value_2";

  KeyValue *visitedEntries[3] = {NULL, NULL, NULL};

  insertHashTable(ht, key, value_1);
  insertHashTable(ht, key, value_2);

  mapHashTable(ht, visitedEntries, testMapHashFn);

  munit_assert_string_equal(value_2, visitedEntries[0]->value);
  munit_assert_uint64(key, ==, visitedEntries[0]->key);

  munit_assert_string_equal(value_1, visitedEntries[1]->value);
  munit_assert_uint64(key, ==, visitedEntries[1]->key);

  // TODO: I think there should be only one entry: (1, value_2)
  // munit_assert_null(visitedEntries[1]);
  munit_assert_null(visitedEntries[2]);

  free(visitedEntries[0]);
  return MUNIT_OK;
}

MunitResult test_mapHashTable_twoEntries(const MunitParameter params[],
                                         void *ht) {
  StgWord key_1 = 1;
  char value_1[] = "value1";
  StgWord key_2 = 2;
  char value_2[] = "value2";

  KeyValue *visitedEntries[3] = {NULL, NULL, NULL};

  insertHashTable(ht, key_1, value_1);
  insertHashTable(ht, key_2, value_2);

  mapHashTable(ht, visitedEntries, testMapHashFn);

  // The traversal order shouldn't be guaranteed.
  if (key_1 == visitedEntries[0]->key) {
    munit_assert_uint64(key_1, ==, visitedEntries[0]->key);
    munit_assert_string_equal(value_1, visitedEntries[0]->value);

    munit_assert_uint64(key_2, ==, visitedEntries[1]->key);
    munit_assert_string_equal(value_2, visitedEntries[1]->value);
  } else {
    munit_assert_uint64(key_2, ==, visitedEntries[0]->key);
    munit_assert_string_equal(value_2, visitedEntries[0]->value);

    munit_assert_uint64(key_1, ==, visitedEntries[1]->key);
    munit_assert_string_equal(value_1, visitedEntries[1]->value);
  }

  munit_assert_null(visitedEntries[2]);

  free(visitedEntries[0]);
  free(visitedEntries[1]);
  return MUNIT_OK;
}

MunitTest mapHashTable_tests[] = {
    {
        "/test_mapHashTable_oneEntry", /* name */
        &test_mapHashTable_oneEntry,   /* test */
        createHashTable,               /* setup */
        destroyHashTable,              /* tear_down */
        MUNIT_TEST_OPTION_NONE,        /* options */
        NULL                           /* parameters */
    },
    {
        "/test_mapHashTable_zeroEntries", /* name */
        &test_mapHashTable_zeroEntries,   /* test */
        createHashTable,                  /* setup */
        destroyHashTable,                 /* tear_down */
        MUNIT_TEST_OPTION_NONE,           /* options */
        NULL                              /* parameters */
    },
    {
        "/test_mapHashTable_twoEntries", /* name */
        &test_mapHashTable_twoEntries,   /* test */
        createHashTable,                 /* setup */
        destroyHashTable,                /* tear_down */
        MUNIT_TEST_OPTION_NONE,          /* options */
        NULL                             /* parameters */
    },
    {
        "/test_mapHashTable_oneDuplicatedEntry", /* name */
        &test_mapHashTable_oneDuplicatedEntry,   /* test */
        createHashTable,                         /* setup */
        destroyHashTable,                        /* tear_down */
        MUNIT_TEST_OPTION_NONE,                  /* options */
        NULL                                     /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
