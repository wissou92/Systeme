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
				if (nmap-> shipInfo [i] .radar .temps > 1) { //pos inconnu
					
				}
				else if (nmap-> shipInfo [i] .radar .distance > 1 && nmap-> shipInfo [i] .radar .distance < 5) {// a porte dattaque + pos connu
					attaque (nmap, i, nmap-> shipInfo [i] .radar .shipPos);
				}
				else {// deplacement vers pos + pos inconnu
					coord_t vect;
					vect .x = (nmap-> shipInfo [i] .radar .shipPos .x - nmap-> shipPosition [i] .x);
					vect .y = (nmap-> shipInfo [i] .radar .shipPos .x - nmap-> shipPosition [i] .x);
					//if (vect .x < 0) vect .x = -vect .x;
					//if (vect .y < 0) vect .y = -vect .y;
					mouvement (nmap, i, );
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
