all: ex libgentle-exit.so

ex: ex.c
	gcc -pg --coverage -g3 -O0 $^ -o $@

libgentle-exit.so: gentle-exit.c
	gcc -shared -fPIC -g3 -O0 $^ -o $@

test: ex libgentle-exit.so
	LD_PRELOAD=./libgentle-exit.so ./ex

clean:
	-rm -f ex libgentle-exit.so gmon.out *.gcov *.gcda *.gcno

.PHONY: all clean test

