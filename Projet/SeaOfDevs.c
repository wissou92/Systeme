/**
 * @author SERHAN Wissam, CRENIER Melvin
 * @version Avril 2019
 * */
#include "navalmap.h"
#include <stdlib.h>
#include <stdio.h>

int J_vs_J (navalmap_t * nmap, int nbTours) 
{
	int * tab = malloc (sizeof (int) * nmap-> nbShips);
	int tour;
	int vainqueur;
	
	for (tour = 0; tour < nbTours; ++tour) {
		vainqueur = detecte_vainqueur (nmap);
		if (vainqueur == -1 || vainqueur >= 0) break;
		printf ("\n--------\nTOUR %d:\n--------\n\n", tour +1);
		algorithme_decision (nmap);
	}
	free (tab);
	return vainqueur;
}


int main (int argc, char ** argv) {
	if (argc != 2) {
		printf ("expected arguments: \"./SeaOfDevs <filename>\"\n");
		exit(1);
	}
	
	info_t fic = read_input (argv [1]);
	navalmap_t * nmap = init_navalmap_wrapper (fic);
	int vainqueur;
	
	/**
	 * code pour joueur contre joueur
	vainqueur = J_vs_J (nmap, fic .nbTours);
	*/
	
	free_navalmap (nmap);
	game_over (vainqueur);
}
