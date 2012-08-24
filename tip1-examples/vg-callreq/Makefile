all: expool-cr expool-nocr

expool-cr: expool.c
	gcc -g3 $^ -o $@

expool-nocr: expool.c
	gcc -DNVALGRIND -g3 $^ -o $@

test-cr: expool-cr
	valgrind --tool=memcheck --leak-check=full $^

test-nocr: expool-nocr
	valgrind --tool=memcheck --leak-check=full $^

clean:
	-rm -f expool-cr expool-nocr

.PHONY: all clean

