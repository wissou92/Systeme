.PHONY: all lib debug

all: lib

lib:
	gcc -g -c -fPIC navalmap.c nm_rect.c
	ar rcs libnm.a navalmap.o nm_rect.o

debug:
	gcc -g -o prog main.c -L. -lnm
