CFLAGS = -Wall -fpic -lm -fprofile-arcs -ftest-coverage

runtest: clean createtest
	./testme

createtest: testme.c
	gcc -o testme -g  testme.c $(CFLAGS)

clean:
	rm -rf *.gcda *.gcno *.dSYM *.gcov testme
