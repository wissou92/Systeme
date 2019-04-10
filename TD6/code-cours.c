#include <stdio.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/time.h>

typedef struct {
	int * i;
	int * moy;
	int * T;
	int id;
	pthread_mutex_t * m;
	pthread_mutex_t * m2;
	pthread_cond_t * c;
} arg_t;

void barrier (int n, arg_t * A) {
	int i;

	pthread_mutex_lock (A->m);
	(*A->i) ++;
	if ((*A->i) < 10)
		pthread_cond_wait (A->c, A->m);
	else {
		for (i = 0; i < (*A->i) - 1; ++i)
			pthread_cond_signal (A->c);
		(* A->i) = 0;
	}
	pthread_mutex_unlock (A->m);
}

void * ft (void * a) {
	int i;
	arg_t * A = (arg_t *) a;

	for (i = A->id * 2; i < (A->id + 1) * 2; ++i) {
		pthread_mutex_lock (A->m);
		(*A->moy) += A->T[i];
		pthread_mutex_unlock (A->m);
	}

	barrier (1, A);
	
	if (! A->id)
		(*A->moy) /= 20;

	barrier (2, A);

	for (i = A->id * 2; i < (A->id + 1) * 2; ++i) {
		A->T[i] = (*A->moy) - A->T[i];
		printf ("#%d -> %d\n", i, A->T[i]);
	}
}

void main () {
	int i; int T [20]; int moy = 0;
	int s = 0;
	arg_t A [10];
	pthread_t tid [10];
	pthread_mutex_t m, m2;
	pthread_cond_t c;
	printf ("Hello World!\n");

	srand (time (NULL));

	pthread_mutex_init (&m, NULL);
	pthread_mutex_init (&m2, NULL);
	pthread_cond_init (&c, NULL);

	for (i = 0; i < 20; ++i)
		T [i] = rand () % 20;

	for (i = 0; i < 10; ++i) {
		A [i] .id = i;
		A [i] .i = &s;
		A [i] .m = &m;
		A [i] .c = &c;	
		A [i] .T = T;
		A [i] .moy = &moy;
		A [i] .m2 = &m2;
		pthread_create (tid+i, NULL, ft, A+i);
	}

	for (i = 0; i < 10; ++i)
		pthread_join (tid [i], NULL);

	pthread_cond_destroy (&c);
	pthread_mutex_destroy (&m);
	pthread_mutex_destroy (&m2);
}
