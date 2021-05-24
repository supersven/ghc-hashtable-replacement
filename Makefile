ghc-hashtable-test:
	mkdir -p bin
	gcc -I includes ghc-hashtable/Hash.c common/*.c test/munit/munit.c test/main.c test/tests.c -o bin/ghc-hashtable-test
	bin/ghc-hashtable-test --iterations 10000

clean:
	rm -r bin
