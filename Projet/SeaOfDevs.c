#include "navalmap.h"
#include <stdlib.h>
#include <stdio.h>


int main (int argc, char ** argv) {
	if (argc != 2) {
		printf ("expected arguments: \"./SeaOfDevs filename\"\n");
		exit(1);
	}
	
	info_t fic = read_input (argv [1]);
	navalmap_t * nmap = init_navalMap (fic);
	
	//printf ("MapType: %s\nTaillex:%d\nTailley:%d\nnbJoueurs:%d\nCmax:%d\nKmax:%d\nnbTours:%d\n", fic.typeCarte, fic.tailleX, fic.tailleY, fic.nbJoueurs, fic.Cmax, fic.Kmax, fic.nbTours);
	exit(0);
}
