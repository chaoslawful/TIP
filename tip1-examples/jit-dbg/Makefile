#gdb_path=/usr/bin/gdb
#outfile_path=/tmp/jitdbg.log

#defs=-DDEFAULT_GDB_PATH='"$(gdb_path)"' -DDEFAULT_OUT_FILE='"$(outfile_path)"'

all: crash libjitdbg.so

crash: crash.c
	gcc -g3 -O0 $^ -o$@

libjitdbg.so: jitdbg.c
	gcc -g3 -O0 -fPIC -shared $(defs) $^ -o $@

test: libjitdbg.so crash
	LD_PRELOAD=./libjitdbg.so ./crash 1

clean:
	rm -f crash libjitdbg.so *.log

.PHONY: all clean test

