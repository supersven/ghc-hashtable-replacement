ghc-hashtable-test:
	mkdir -p bin
	gcc -I includes ghc-hashtable/Hash.c common/*.c test/munit/munit.c test/*.c -o bin/ghc-hashtable-test
	bin/ghc-hashtable-test --iterations 10000

ghc-hashtable-test-debug:
	mkdir -p bin
	gcc -ggdb -I includes ghc-hashtable/Hash.c common/*.c test/munit/munit.c test/*.c -o bin/ghc-hashtable-test-debug

clean:
	rm -r bin
