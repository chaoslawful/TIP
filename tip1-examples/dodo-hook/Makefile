EXCL_SYMS :=
CFLAGS := -g3 -O0 -finstrument-functions
ifneq ($(EXCL_SYMS),)
	CFLAGS += -finstrument-functions-exclude-function-list=$(EXCL_SYMS)
endif

all: ex libdodo-hook.so

ex: ex.c
	gcc $(CFLAGS) $^ -o $@

libdodo-hook.so: dodo-hook.c
	gcc -shared -fPIC $(CFLAGS) $^ -o $@

test: ex libdodo-hook.so
	LD_PRELOAD=./libdodo-hook.so ./ex

clean:
	-rm -f ex libdodo-hook.so trace.out.*

.PHONY: all clean test

