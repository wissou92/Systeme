run: compile
	./meta

compile:  fonction.o dossier.o main.o 
	gcc -o fonction fonction.o meta.o

dossier.o: dossier.c
	gcc -o dossier.o -c dossier.c -Wall

fonction.o: fonction.c
	gcc -o fonction.o -c fonction.c -Wall

meta.o: main.c fonction.h
	gcc -o main.o -c main.c -Wall

clean:
	rm -rf *.o
