#include <FakedRtsIncludes.h>
#include <Hash.h>
#include <stdlib.h>
#include "munit/munit.h"

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

MunitResult test_removeHashTable(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    insertHashTable(ht, key, value);
    char* removedValue = removeHashTable(ht, key, value);
    char* lookedUpValue = lookupHashTable(ht, key);

    munit_assert_string_equal(value, removedValue);
    munit_assert_null(lookedUpValue);

    return MUNIT_OK;
}

MunitResult test_keyCountHashTable(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    insertHashTable(ht, key, value);
    int afterInsertCount = keyCountHashTable(ht);

    munit_assert_int(afterInsertCount, ==, 1);

    return MUNIT_OK;
}

MunitResult test_keyCountHashTable_emptyTable(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    int count = keyCountHashTable(ht);

    munit_assert_int(count, ==, 0);

    return MUNIT_OK;
}

MunitResult test_keysHashTable(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    insertHashTable(ht, key, value);

    StgWord* buf = malloc(sizeof(StgWord));
    int count = keysHashTable(ht, buf, 1);

    munit_assert_uint64(buf[0], ==, 1);
    munit_assert_int(count, ==, 1);

    return MUNIT_OK;
}

MunitResult test_keysHashTable_emptyArray(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    insertHashTable(ht, key, value);

    StgWord* buf = malloc(sizeof(StgWord));
    int count = keysHashTable(ht, buf, 0);

    munit_assert_uint64(buf[0], ==, 0);
    munit_assert_int(count, ==, 0);

    return MUNIT_OK;
}

MunitResult test_keysHashTable_emptyTable(const MunitParameter params[], void* ht) {
    StgWord* buf = malloc(sizeof(StgWord));
    int count = keysHashTable(ht, buf, 0);

    munit_assert_uint64(buf[0], ==, 0);
    munit_assert_int(count, ==, 0);

    return MUNIT_OK;
}

static void*
createHashTable(const MunitParameter params[], void* user_data) {
  return allocHashTable();
}

static void
destroyHashTable(void* ht) {
  freeHashTable(ht, NULL);
}

MunitTest tests[] = {
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
  {
    "/test_removeHashTable", /* name */
    &test_removeHashTable, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_keyCountHashTable", /* name */
    &test_keyCountHashTable, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_keyCountHashTable_emptyTable", /* name */
    &test_keyCountHashTable_emptyTable, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_keysHashTable", /* name */
    &test_keysHashTable, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_keysHashTable_emptyArray", /* name */
    &test_keysHashTable_emptyArray, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_keysHashTable_emptyTable", /* name */
    &test_keysHashTable_emptyTable, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  /* Mark the end of the array with an entry where the test
   * function is NULL */
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
