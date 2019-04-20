#include "navalmap.h"
#include <stdlib.h>
#include <stdio.h>



int main (int argc, char ** argv) {
	if (argc != 2) {
		printf ("expected arguments: \"./SeaOfDevs filename\"\n");
		exit(1);
	}
	info_t fic = read_input (argv [1]);
	navalmap_t * nmap = init_navalmap_wrapper (fic);
	int tour, vainqueur;
	int * tab = malloc (sizeof (int) * nmap-> nbShips);
	
	for (tour = 0; tour < fic .nbTours; ++tour) {
		joueur_restant (nmap, tab);
		vainqueur = detecte_vainqueur (tab, nmap-> nbShips);
		if (vainqueur == -1 || vainqueur >= 0) break;
		printf ("\n-------\nTOUR %d:\n-------\n\n", tour +1);
		algorithme_decision (nmap);
	}
	
	free (tab);
	free_navalmap (nmap);
	game_over (vainqueur);
}
