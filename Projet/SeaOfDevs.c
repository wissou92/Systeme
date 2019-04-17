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
	int tour;
	
	for (tour = 0; tour < nmap-> nbTours; ++tour) {
		printf ("TOUR %d:\n\n", tour +1);
		algorithme_decision (nmap);
	}
	
	
	
	free_navalmap (nmap);
	exit(0);
}
