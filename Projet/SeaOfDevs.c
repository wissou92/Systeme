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
	
	for (tour = 0; tour < fic .nbTours; ++tour) {
		vainqueur = victoire (elimination (nmap), nmap->nbShips);
		if (vainqueur != -1) break;
		printf ("\n-------\nTOUR %d:\n-------\n\n", tour +1);
		algorithme_decision (nmap);
	}

	free_navalmap (nmap);
	game_over (vainqueur);
}
