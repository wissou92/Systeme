#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

typedef struct {
	int * tab;
	int taille;
}tableau;

tableau * init_tab (int n) {
	int i;
	
	tableau * T;
	T.tab = malloc (sizeof (int) * n);
	T.taille = n;
	for (i=0; i<n; ++i) {
		tab[i] = rand () % 100;
	}
	
	return T;
}

void * fct1 (void * arg) {
	printf ("Hello World!\n");
	(void) arg;
	pthread_exit (NULL);
}

void * fct2 (void * arg) {
	printf("Nombre aléatoire affiché par le thread: %d\n", *(int *) arg);
	pthread_exit(NULL);
}

void * fct3 (void * arg) {
	*(int *) arg = rand() % 100;
	pthread_exit(NULL);
}

void * fct4 (void * arg) {
	int i;
	int moyenne = 0;

	for (i=0; i<5; ++i) {
		moyenne += ((int *) arg)[i];
	}
	
	printf("La moyenne du tableau de taille 5 est: %d\n", moyenne/5);
	pthread_exit(NULL);
}

int main (void) {
	srand (getpid ());
	tableau tab = init_tab(5);
	int nb_alea = rand () % 100;
	int * nombre = malloc (sizeof (int));
	pthread_t thread1, thread2, thread3, thread4;
	
	
	
	if (pthread_create (&thread1, NULL, fct1, NULL) != 0) {
		perror ("pthread_create");
		return EXIT_FAILURE;
	}
	if (pthread_create (&thread2, NULL, fct2, (void *) &nb_alea) != 0) {
		perror ("pthread_create");
		return EXIT_FAILURE;
	}
	if (pthread_create (&thread3, NULL, fct3, (void *) nombre) != 0) {
		perror ("pthread_create");
		return EXIT_FAILURE;
	}
	if (pthread_create (&thread4, NULL, fct4, (void *) tab) != 0) {
		perror ("pthread_create");
		return EXIT_FAILURE;
	}
	
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);
	pthread_join (thread3, NULL);
	pthread_join (thread4, NULL);
	
	printf("Nombre aléatoire affiché par le main: %d\n", *nombre);
	
	return EXIT_SUCCESS;
}
