#include <FakedRtsIncludes.h>
#include <Hash.h>
#include <stdlib.h>
#include "munit/munit.h"
#include "lib.h"

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

MunitResult test_keyCountHashTable_sameKey(const MunitParameter params[], void* ht) {
    StgWord key = 1;

    insertHashTable(ht, key, "value_1");
    insertHashTable(ht, key, "value_2");
    insertHashTable(ht, key, "value_3");
    int afterInsertCount = keyCountHashTable(ht);

    munit_assert_int(afterInsertCount, ==, 3);

    // TODO: I think the count should be 1!
    // munit_assert_int(afterInsertCount, ==, 3);

    return MUNIT_OK;
}

MunitTest keyCountHashTable_tests[] = {
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
    "/test_keyCountHashTable_sameKey", /* name */
    &test_keyCountHashTable_sameKey, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  /* Mark the end of the array with an entry where the test
   * function is NULL */
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
