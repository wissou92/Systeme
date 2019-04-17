#include "nm_player.h"
#include "navalmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void choix_action (navalmap_t * nmap, const int shipID, int choix, void * arg) {
	
	switch (choix) {
		case 0:				// aucune action
			aucun (nmap, shipID);
			break;
		case 1:				// mouvement
			mouvement (nmap, shipID, *(coord_t *) arg);
			break;
		case 2: 			// attaque
			attaque (nmap, shipID, *(coord_t *) arg);
			break;
		case 3:				// radar
			radarscn (nmap, shipID);
			break;
		default:			// défaut normalement jamais effécuté
			printf ("choix invalide, non-action effectuée\n");
			aucun (nmap, shipID);
			break;
	}
}

void algorithme_decision (navalmap_t * nmap) {
	int i; pid_t * pid = malloc (nmap-> nbShips * sizeof (pid_t));
	int dscrpt_pere [2];										// Pour communiquer au pere (les fils écrivent dedans)
	int dscrpt_fils [nmap-> nbShips][2];						// Pour communiquer aux fils (le père écrit dedans)
	int * choix = malloc (sizeof (int) * nmap-> nbShips);
	
	for (i=0; i<nmap-> nbShips; ++i) {
		pid [i] = fork ();
		switch (pid [i]) {
			
			case -1: // erreur
				printf ("fork error\n");
				exit (1);
				break;
				
			case 0: // fils
				close (dscrpt_pere [0]);
				close (dscrpt_fils [i][1]);
				
				ship_t info;
				read (dscrpt_fils [i][0], &info, sizeof (ship_t));

				int decision;
				
				if (info .radar .temps > 1) { //pos inconnu ou radar trop vieux
					// Il doit faire radar renvoyer 3
					decision = 3;
				}
				else if (nmap-> shipInfo [i] .radar .distance > 1 && nmap-> shipInfo [i] .radar .distance < 5) {// a porte dattaque + pos connu
					// Il doit attaquer renvoyer 2
					decision = 2;
				}
				else {// deplacement vers pos + pos connu
					// Il doit se déplacer renvoyer 1
					decision = 1;
				}
				write (dscrpt_pere [1], &decision, sizeof (int));
				exit (2);
				break;
				
			default: // père
				close (dscrpt_fils [i][0]);
				write (dscrpt_fils [i][1], &(nmap-> shipInfo [i], sizeof (ship_t));
				read (dscrpt_pere [0], choix [i], sizeof (int));
				break;
		}
	}
	for (i=0; i<nmap-> nbShips; ++i) {
		wait (NULL);
		if (choix [i] == 3 || choix [i] == 0)
		{
			choix_action (nmap, i, choix [i], NULL);
		}
		else if (choix [i] == 1) 
		{
			coord_t cible = nmap-> shipInfo [i] .radar .shipPos;		
			coord_t mouv;
			
			choix_action (nmap, i, choix [i], (void *) &mouv);
		}
		else if (choix [i] == 2)
		{
			coord_t cible;
			choix_action (nmap, i, choix [i], (void *) &cible);
		}
	}
	free (choix); free (pid);
}


					//coord_t vect;
					//vect .x = (nmap-> shipInfo [i] .radar .shipPos .x - nmap-> shipPosition [i] .x);
					//vect .y = (nmap-> shipInfo [i] .radar .shipPos .x - nmap-> shipPosition [i] .x);
					//if (vect .x < 0) vect .x = -vect .x;
					//if (vect .y < 0) vect .y = -vect .y;
