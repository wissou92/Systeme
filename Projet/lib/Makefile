INC=./include/
.PHONY: all lib debug clean

all: lib

lib:
	gcc -g -c -fPIC $(INC)*.c
	ar rcs libnm.a *.o

debug:
	gcc -g -o prog main.c -L. -lnm

clean:
	rm -rf *.o
	rm -rf libnm.a
