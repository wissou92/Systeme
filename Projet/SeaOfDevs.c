#include "navalmap.h"
#include <stdlib.h>
#include <stdio.h>


int main (int argc, char ** argv) {
	if (argc != 2) {
		printf ("expected argument: \"./SeaOfDevs filename\"\n");
		exit(1);
	}
	
	read_input (argv [1]);
	
	exit(0);
}
