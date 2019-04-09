#include "nm_player.h"
#include "navalmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void algorithme_decision (navalmap_t * nmap) {
	int i; pid_t * pid = malloc (nmap-> nbShips * sizeof (pid_t));
	for (i=0; i<nmap-> nbShips; ++i) {
		pid [i] = fork ();
		switch (pid [i]) {
			case -1: // erreur
				printf ("fork error\n");
				exit (1);
				break;
			case 0: // fils
				// recuperer infos
				if () { //pos inconnu
					
				}
				else if () {// a porte dattaque + pos connu
					
				}
				else {// deplacement vers pos + pos inconnu
					
				}
				exit (2);
				break;
			default: // père
				
				break;
		}
	}
	for (i=0; i<nmap-> nbShips; ++i) {
		wait (NULL);
	}
}
