#include "munit/munit.h"
#include "tests.h"

static const MunitSuite suite = {
  "/simple-tests", /* name */
  tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

int main (int argc, char* argv[]) {
  /* Use µnit here. */
  return munit_suite_main(&suite, NULL, argc, argv);
}
