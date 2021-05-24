#include <FakedRtsIncludes.h>
#include <Hash.h>
#include <stdlib.h>
#include "munit/munit.h"

MunitResult test_insertHashTable_duplicatekey(const MunitParameter params[], void* ht) {
    StgWord key = 1;

    insertHashTable(ht, key, "value_1");
    insertHashTable(ht, key, "value_2");
    char* lookedUpValue = lookupHashTable(ht, key);

    munit_assert_string_equal("value_2", lookedUpValue);

    return MUNIT_OK;
}

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

MunitResult test_removeHashTable_twoEntriesDuplicatedKey(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value_1[] = "value_1";
    char value_2[] = "value_2";

    insertHashTable(ht, key, value_1);
    insertHashTable(ht, key, value_2);

    char* removedValue = removeHashTable(ht, key, value_1);
    char* lookedUpValue = lookupHashTable(ht, key);

    munit_assert_string_equal(value_1, removedValue);

    // TODO: I think both entries should have been removed!
    // munit_assert_null(lookedUpValue);
    munit_assert_string_equal(value_2, lookedUpValue);

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

MunitResult test_keysHashTable(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    insertHashTable(ht, key, value);

    StgWord* buf = munit_new(StgWord);
    int count = keysHashTable(ht, buf, 1);

    munit_assert_uint64(buf[0], ==, 1);
    munit_assert_int(count, ==, 1);

    return MUNIT_OK;
}

MunitResult test_keysHashTable_emptyArray(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    insertHashTable(ht, key, value);

    StgWord* buf = munit_new(StgWord);
    int count = keysHashTable(ht, buf, 0);

    munit_assert_uint64(buf[0], ==, 0);
    munit_assert_int(count, ==, 0);

    return MUNIT_OK;
}

MunitResult test_keysHashTable_emptyTable(const MunitParameter params[], void* ht) {
    StgWord* buf = munit_new(StgWord);
    int count = keysHashTable(ht, buf, 0);

    munit_assert_uint64(buf[0], ==, 0);
    munit_assert_int(count, ==, 0);

    return MUNIT_OK;
}

typedef struct KeyValue_ {
  StgWord key;
  char* value;
} KeyValue;

void testMapHashFn(void *data, StgWord key, const void *value) {
    KeyValue** visitedEntries = (KeyValue**) data;

    for(int i = 0; i < 3; i++) {
      if(visitedEntries[i] == NULL){
        KeyValue* kv = munit_new(KeyValue);
        kv->key = key;
        kv->value = (char*) value;
        visitedEntries[i] = kv;

        break;
      }
    }
}

MunitResult test_mapHashTable_zeroEntries(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    KeyValue* visitedEntries[3] = {NULL, NULL,NULL};

    mapHashTable(ht, visitedEntries, testMapHashFn);

    munit_assert_null(visitedEntries[0]);
    munit_assert_null(visitedEntries[1]);
    munit_assert_null(visitedEntries[2]);

    return MUNIT_OK;
}

MunitResult test_mapHashTable_oneEntry(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    KeyValue* visitedEntries[3] = {NULL, NULL,NULL};

    insertHashTable(ht, key, value);

    mapHashTable(ht, visitedEntries, testMapHashFn);

    munit_assert_string_equal(value, visitedEntries[0]->value);
    munit_assert_uint64(key, ==, visitedEntries[0]->key);
    munit_assert_null(visitedEntries[1]);
    munit_assert_null(visitedEntries[2]);

    free(visitedEntries[0]);
    return MUNIT_OK;
}


MunitResult test_mapHashTable_oneDuplicatedEntry(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value_1[] = "value_1";
    char value_2[] = "value_2";

    KeyValue* visitedEntries[3] = {NULL, NULL,NULL};

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

MunitResult test_mapHashTable_twoEntries(const MunitParameter params[], void* ht) {
    StgWord key_1 = 1;
    char value_1[] = "value1";
    StgWord key_2 = 2;
    char value_2[] = "value2";

    KeyValue* visitedEntries[3] = {NULL, NULL,NULL};

    insertHashTable(ht, key_1, value_1);
    insertHashTable(ht, key_2, value_2);

    mapHashTable(ht, visitedEntries, testMapHashFn);

    // The traversal order shouldn't be guaranteed.
    if(key_1 == visitedEntries[0]->key) {
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

void testMapHashFnKeys(void *data, StgWord *key, const void *value) {
    KeyValue** visitedEntries = (KeyValue**) data;

    for(int i = 0; i < 3; i++) {
      if(visitedEntries[i] == NULL){
        KeyValue* kv = munit_new(KeyValue);
        kv->key = *key;
        kv->value = (char*) value;
        visitedEntries[i] = kv;

        break;
      }
    }
}

MunitResult test_mapHashTableKeys_zeroEntries(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    KeyValue* visitedEntries[3] = {NULL, NULL,NULL};

    mapHashTableKeys(ht, visitedEntries, testMapHashFnKeys);

    munit_assert_null(visitedEntries[0]);
    munit_assert_null(visitedEntries[1]);
    munit_assert_null(visitedEntries[2]);

    return MUNIT_OK;
}

MunitResult test_mapHashTableKeys_oneEntry(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value[] = "value";

    KeyValue* visitedEntries[3] = {NULL, NULL,NULL};

    insertHashTable(ht, key, value);

    mapHashTableKeys(ht, visitedEntries, testMapHashFnKeys);

    munit_assert_string_equal(value, visitedEntries[0]->value);
    munit_assert_uint64(key, ==, visitedEntries[0]->key);
    munit_assert_null(visitedEntries[1]);
    munit_assert_null(visitedEntries[2]);

    free(visitedEntries[0]);
    return MUNIT_OK;
}

MunitResult test_mapHashTableKeys_oneDuplicatedEntry(const MunitParameter params[], void* ht) {
    StgWord key = 1;
    char value_1[] = "value_1";
    char value_2[] = "value_2";

    KeyValue* visitedEntries[3] = {NULL, NULL,NULL};

    insertHashTable(ht, key, value_1);
    insertHashTable(ht, key, value_2);

    mapHashTableKeys(ht, visitedEntries, testMapHashFnKeys);

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

MunitResult test_mapHashTableKeys_twoEntries(const MunitParameter params[], void* ht) {
    StgWord key_1 = 1;
    char value_1[] = "value1";
    StgWord key_2 = 2;
    char value_2[] = "value2";

    KeyValue* visitedEntries[3] = {NULL, NULL,NULL};

    insertHashTable(ht, key_1, value_1);
    insertHashTable(ht, key_2, value_2);

    mapHashTableKeys(ht, visitedEntries, testMapHashFnKeys);

    // The traversal order shouldn't be guaranteed.
    if(key_1 == visitedEntries[0]->key) {
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
    "/test_removeHashTable_twoEntriesDuplicatedKey", /* name */
    &test_removeHashTable_twoEntriesDuplicatedKey, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },  {
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
  {
    "/test_mapHashTable_oneEntry", /* name */
    &test_mapHashTable_oneEntry, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_mapHashTable_zeroEntries", /* name */
    &test_mapHashTable_zeroEntries, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_mapHashTable_twoEntries", /* name */
    &test_mapHashTable_twoEntries, /* test */
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
  }, // test_insertHashTable_duplicatekey
  {
    "/test_insertHashTable_duplicatekey", /* name */
    &test_insertHashTable_duplicatekey, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_mapHashTable_oneDuplicatedEntry", /* name */
    &test_mapHashTable_oneDuplicatedEntry, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_mapHashTableKeys_zeroEntries", /* name */
    &test_mapHashTableKeys_zeroEntries, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_mapHashTableKeys_oneEntry", /* name */
    &test_mapHashTableKeys_oneEntry, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_mapHashTableKeys_oneDuplicatedEntry", /* name */
    &test_mapHashTableKeys_oneDuplicatedEntry, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/test_mapHashTableKeys_twoEntries", /* name */
    &test_mapHashTableKeys_twoEntries, /* test */
    createHashTable, /* setup */
    destroyHashTable, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  /* Mark the end of the array with an entry where the test
   * function is NULL */
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};
