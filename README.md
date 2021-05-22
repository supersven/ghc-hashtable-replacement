Please see https://gitlab.haskell.org/ghc/ghc/-/issues/19887 for details (and what this is all about).

To build and run tests (probably AMD64 only) call `make`:

```
[sven@colossus:~/projects/ghc-hashtable-replacement]$ make
mkdir -p bin
gcc -I includes ghc-hashtable/Hash.c common/*.c test/munit/munit.c test/main.c test/tests.c -o bin/ghc-hashtable-test
bin/ghc-hashtable-test
Running test suite with seed 0x13b5ac04...
/simple-tests/test_lookupHashTable   [ OK    ] [ 0.00000521 / 0.00000452 CPU ]
/simple-tests/test_lookupHashTable_emptyTable[ OK    ] [ 0.00000130 / 0.00000066 CPU ]
/simple-tests/test_removeHashTable   [ OK    ] [ 0.00000631 / 0.00000559 CPU ]
/simple-tests/test_keyCountHashTable [ OK    ] [ 0.00000343 / 0.00000317 CPU ]
/simple-tests/test_keyCountHashTable_emptyTable[ OK    ] [ 0.00000080 / 0.00000051 CPU ]
/simple-tests/test_keysHashTable     [ OK    ] [ 0.00000399 / 0.00000369 CPU ]
/simple-tests/test_keysHashTable_emptyArray[ OK    ] [ 0.00000181 / 0.00000167 CPU ]
/simple-tests/test_keysHashTable_emptyTable[ OK    ] [ 0.00000056 / 0.00000040 CPU ]
8 of 8 (100%) tests successful, 0 (0%) test skipped.
```
