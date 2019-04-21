#include "nm_player.h"
#include "navalmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void game_over (int vainqueur)
{
	if (vainqueur >= 0) { 
		printf ("J%d a gagné\n", vainqueur + 1);
	}
	else printf ("Aucun joueur restant\n");
	exit(0);
}

int detecte_vainqueur (navalmap_t nmap) {
	int i;
	int compteur = 0, gagnant = -1;
	for (i = 0; i<nmap-> nbShips; ++i) {
		if (nmap-> shipInfo [i] .en_vie == 1)
		{
			compteur++;
			gagnant = i;
		}
	}
	if (compteur == 0 || compteur == 1) return gagnant;
	else return -2;
}

void choix_action (navalmap_t * nmap, const int shipID, int choix, void * arg) {
	if (nmap-> shipInfo [shipID] .radar .temps != -1)  {
		++nmap-> shipInfo [shipID] .radar .temps;
	}
	switch (choix) {
		case -1:
			printf ("J%d Hors-Service\n");
			break;
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

coord_t vecteur_deplacement (coord_t ship_mv, coord_t cible, int distance) { 
	coord_t mouv;
	if (distance == 1 || distance == 0) {
		if (cible .x == ship_mv .x)
		{
			if (cible .y == ship_mv .y)
			{
				mouv .x = rand () %2;
				mouv .y = rand () %2;
			}
			else if(cible .y < ship_mv .y) 
			{
				mouv .x = 0;
				mouv .y = 1;
			}
			else 
			{
				mouv .x = 0;
				mouv .y = -1;
			}
		}
		else if (cible .x < ship_mv .x) {
			if (cible .y == ship_mv .y) {
				mouv .x = 1;
				mouv .y = 0;
			}
			else if (cible .y < ship_mv .y) {
				mouv .x = 1;
				mouv .y = 1;
			}
			else {
				mouv .x = 1;
				mouv .y = -1;
			}
		}
		else {
			if (cible .y == ship_mv .y) {
				mouv .x = -1;
				mouv .y = 0;
			}
			else if (cible .y < ship_mv .y) {
				mouv .x = -1;
				mouv .y = 1;
			}
			else {
				mouv .x = -1;
				mouv .y = -1;
			}
		}
	}
	else if (cible .x == ship_mv .x) 
	{
		if (cible .y < ship_mv .y)
		{
			mouv .x = 0;
			mouv .y = -2;
		}
		else
		{
			mouv .x = 0;
			mouv .y = 2;
		}
	}
	else if (cible .y == ship_mv .y)
	{
		if (cible .x < ship_mv .x)
		{
			mouv .x = -2;
			mouv .y = 0;
		}
		else
		{
			mouv .x = 2;
			mouv .y = 0;
		}
	}
	else if (cible .x < ship_mv .x)
	{
		if (cible .y < ship_mv .y)
		{
			mouv .x = -1;
			mouv .y = -1;
		}
		else
		{
			mouv .x = -1;
			mouv .y = 1;
		}
	}
	else
	{
		if (cible .y < ship_mv .y)
		{
			mouv .x = 1;
			mouv .y = -1;
		}
		else
		{
			mouv .x = 1;
			mouv .y = 1;
		}
	}
	return mouv;
}

void algorithme_decision (navalmap_t * nmap) {
	int i; pid_t * pid = malloc (nmap-> nbShips * sizeof (pid_t));
	int dscrpt_pere [2];										// Pour communiquer au pere (les fils écrivent dedans)
	int dscrpt_fils [nmap-> nbShips][2];						// Pour communiquer aux fils (le père écrit dedans)
	int * choix = malloc (sizeof (int) * nmap-> nbShips);
	
	if (pipe (dscrpt_pere) == -1) {
		printf ("pipe error\n");
		exit (1);
	}
	
	for (i = 0; i< nmap-> nbShips; ++i) {
		if (pipe (dscrpt_fils [i]) == -1) {
		printf ("pipe error\n");
		exit (1);
		}
	}

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
				
				if (info .en_vie == 0) { // navire coulé
					decision = -1;
				}
				else if (info .radar .temps > 1 || info .radar .temps == -1) { //pos inconnu ou radar trop vieux
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
				write (dscrpt_fils [i][1], &(nmap-> shipInfo [i]), sizeof (ship_t));
				read (dscrpt_pere [0], choix + i, sizeof (int));
				break;
		}
	}
	for (i=0; i<nmap-> nbShips; ++i) {
		wait (NULL);
		
		if (choix [i] == -1) {
			choix_action (nmap, i, choix [i], NULL);
		}
		else if (choix [i] == 3 || choix [i] == 0) 	// radar || non-action
		{
			choix_action (nmap, i, choix [i], NULL);
		}
		else if (choix [i] == 1) 				// mouvement
		{
			coord_t mouv = vecteur_deplacement (nmap-> shipPosition [i], nmap-> shipInfo [i] .radar .shipPos, nmap-> shipInfo [i] .radar .distance);
			choix_action (nmap, i, choix [i], (void *) &mouv);
		}
		else if (choix [i] == 2) 				// attaque
		{
			coord_t cible = nmap-> shipInfo [i] .radar .shipPos;
			choix_action (nmap, i, choix [i], (void *) &cible);
		}
		printf ("J%d position (%d, %d)\n", i + 1, nmap-> shipPosition [i] .x, nmap-> shipPosition [i] .y);
		printf ("coque: %d\nkerozene: %d\n\n", nmap-> shipInfo [i] .coque, nmap-> shipInfo [i] . kerozene);
	}
	free (choix); free (pid);
}
