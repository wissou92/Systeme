.PHONY: all lib debug clean

all: lib

lib:
	gcc -g -c -fPIC ./include/navalmap.c ./include/nm_rect.c
	ar rcs libnm.a navalmap.o nm_rect.o

debug:
	gcc -g -o prog main.c -L. -lnm

clean:
	rm -rf *.o
	rm -rf libnm.a
