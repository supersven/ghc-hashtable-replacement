#include "lib.h"
#include "Hash.h"

bool countingIterator(void *counter, StgWord key, const void *value) {
  (*(int *)counter)++;
  return true;
}

MunitResult
test_iterHashTable_countEmptyHashTable(const MunitParameter params[],
                                       void *ht) {
  int counter = 0;
  iterHashTable(ht, &counter, countingIterator);

  munit_assert_int(counter, ==, 0);

  return MUNIT_OK;
}

MunitResult
test_iterHashTable_countSingletonHashTable(const MunitParameter params[],
                                           void *ht) {
  int counter = 0;
  insertHashTable(ht, 1, NULL);

  iterHashTable(ht, &counter, countingIterator);

  munit_assert_int(counter, ==, 1);

  return MUNIT_OK;
}

MunitResult
test_iterHashTable_countTwoItemHashTable(const MunitParameter params[],
                                         void *ht) {
  int counter = 0;
  insertHashTable(ht, 1, NULL);
  insertHashTable(ht, 2, NULL);

  iterHashTable(ht, &counter, countingIterator);

  munit_assert_int(counter, ==, 2);

  return MUNIT_OK;
}

struct KeyAndValue {
  int key;
  char *value;
} KeyAndValue;

bool keyAndValueIterator(void *data, StgWord key, const void *value) {
  struct KeyAndValue *kv = data;
  kv->key = key;
  kv->value = (char *)value;

  return true;
}

MunitResult test_iterHashTable_checkKeyAndValue(const MunitParameter params[],
                                                void *ht) {
  struct KeyAndValue *data = malloc(sizeof(KeyAndValue) + sizeof("value"));

  insertHashTable(ht, 1, "value");

  iterHashTable(ht, data, keyAndValueIterator);

  munit_assert_int(data->key, ==, 1);
  munit_assert_string_equal(data->value, "value");

  free(data);

  return MUNIT_OK;
}

bool countingIterator_stopAfterFirstItem(void *counter, StgWord key,
                                         const void *value) {
  (*(int *)counter)++;
  return false;
}

MunitResult test_iterHashTable_stopAfterFirstItem(const MunitParameter params[],
                                                  void *ht) {
  int counter = 0;
  insertHashTable(ht, 1, NULL);
  insertHashTable(ht, 2, NULL);

  iterHashTable(ht, &counter, countingIterator_stopAfterFirstItem);

  munit_assert_int(counter, ==, 1);

  return MUNIT_OK;
}

MunitTest iterHashTable_tests[] = {
    {
        "/test_iterHashTable_countEmptyHashTable", /* name */
        &test_iterHashTable_countEmptyHashTable,   /* test */
        createHashTable,                           /* setup */
        destroyHashTable,                          /* tear_down */
        MUNIT_TEST_OPTION_NONE,                    /* options */
        NULL                                       /* parameters */
    },
    {
        "/test_iterHashTable_countSingletonHashTable", /* name */
        &test_iterHashTable_countSingletonHashTable,   /* test */
        createHashTable,                               /* setup */
        destroyHashTable,                              /* tear_down */
        MUNIT_TEST_OPTION_NONE,                        /* options */
        NULL                                           /* parameters */
    },
    {
        "/test_iterHashTable_countTwoItemHashTable", /* name */
        &test_iterHashTable_countTwoItemHashTable,   /* test */
        createHashTable,                             /* setup */
        destroyHashTable,                            /* tear_down */
        MUNIT_TEST_OPTION_NONE,                      /* options */
        NULL                                         /* parameters */
    },
    {
        "/test_iterHashTable_checkKeyAndValue", /* name */
        &test_iterHashTable_checkKeyAndValue,   /* test */
        createHashTable,                        /* setup */
        destroyHashTable,                       /* tear_down */
        MUNIT_TEST_OPTION_NONE,                 /* options */
        NULL                                    /* parameters */
    },
    {
        "/test_iterHashTable_stopAfterFirstItem", /* name */
        &test_iterHashTable_stopAfterFirstItem,   /* test */
        createHashTable,                          /* setup */
        destroyHashTable,                         /* tear_down */
        MUNIT_TEST_OPTION_NONE,                   /* options */
        NULL                                      /* parameters */
    },

    /* Mark the end of the array with an entry where the test
     * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
