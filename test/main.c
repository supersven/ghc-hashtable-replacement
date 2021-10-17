#include "munit/munit.h"
#include "tests.h"
#include <stddef.h>

static MunitSuite other_suites[] = {
    {"/mapHashTableKeys", mapHashTableKeys_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
    {"/keyCountHashTable", keyCountHashTable_tests, NULL, 1,
     MUNIT_SUITE_OPTION_NONE},
    {"/keysHashTable", keysHashTable_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
    {"/removeHashTable", removeHashTable_tests, NULL, 1,
     MUNIT_SUITE_OPTION_NONE},
    {"/lookupHashTable", lookupHashTable_tests, NULL, 1,
     MUNIT_SUITE_OPTION_NONE},
    {"/insertHashTable", insertHashTable_tests, NULL, 1,
     MUNIT_SUITE_OPTION_NONE},
    {"/mapHashTable", mapHashTable_tests, NULL, 1,
     MUNIT_SUITE_OPTION_NONE},
    {"/iterHashTable", iterHashTable_tests, NULL, 1,
     MUNIT_SUITE_OPTION_NONE},
    {"/insertStrHashTable", insertStrHashTable_tests, NULL, 1,
     MUNIT_SUITE_OPTION_NONE},
    {"/lookupStrHashTable", lookupHashTable_tests, NULL, 1,
     MUNIT_SUITE_OPTION_NONE},
    {NULL, NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE}};

static const MunitSuite suite = {
    "/tests",               /* name */
    NULL,                   /* tests */
    other_suites,           /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[]) {
  /* Use µnit here. */
  return munit_suite_main(&suite, NULL, argc, argv);
}
