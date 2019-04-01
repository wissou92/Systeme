#include "navalmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

/*navalmap_t * read_fileInput (char * fileName) {
	
	int fd = open (fileName, O_RDONLY);
	
	if (fd == -1) {
		fprintf (stderr, "erreur lecture fichier\n");
		exit (EXIT_FAILURE);
	}
	
	int information = 1; // Pour voir quelle information on a en face de nous
	int i = 0;
	int j = 0;
	
	
	int nb_bytes;
	int nbShips;
	int Cmax, Kmax, nbTours;
	
	map_t mapType = MAP_TOTAL;
	coord_t mapSize;
	
	char * string = malloc (sizeof (char)*200);
	
	nb_bytes = read (fd, &string, 200);
	string [nb_bytes] = '\0';
	
	
	
	while (string[i] != '\0') {
		char * string_tmp = malloc (sizeof (char)* 15);
		j = 0;
		while (string [i] != '\0' && string [i] != ';' && string [i] != '\n') {
			string_tmp [j] = string [i];
			++i;
			++j;
		}
		++i;
		string_tmp [j] = '\0';
		printf ("string_tmp: %s", string_tmp);
		
		switch(information) {
			int taille;
			case 1: // Type de map
				if (strcmp (string_tmp, "rectangle") == 0)
				{
					mapType = MAP_RECT;
				}
				break;
			
			case 2: // Taille X
				taille = j-1;
				mapSize.x = 0;
				for (int n=0; n<j+1; ++n) {
					mapSize.x += atoi (&string[n]) * 10^(taille);
					--taille;
				}
				break;
			
			case 3: // Taille Y
				taille = j-1;
				mapSize.y = 0;
				for (int n=0; n<j+1; ++n) {
					mapSize.y += atoi (&string[n]) * 10^(taille);
					--taille;
				}
				break;
			
			case 4: // nbJoueurs
				taille = j-1;
				nbShips = 0;
				for (int n=0; n<j+1; ++n) {
					nbShips += atoi (&string[n]) * 10^(taille);
					--taille;
				}
				break;
			
			case 5: // Cmax
				taille = j-1;
				Cmax = 0;
				for (int n=0; n<j+1; ++n) {
					Cmax += atoi (&string[n]) * 10^(taille);
					--taille;
				}
				break;
			
			case 6: // Kmax
				taille = j-1;
				Kmax = 0;
				for (int n=0; n<j+1; ++n) {
					Kmax += atoi (&string[n]) * 10^(taille);
					--taille;
				}
				break;
			
			case 7: // nbTours
				taille = j-1;
				nbTours = 0;
				for (int n=0; n<j+1; ++n) {
					nbTours += atoi (&string[n]) * 10^(taille);
					--taille;
				}
				break;
			default:
				
				break;
		}
		++information;
		free (string_tmp);
	}
	free (string);
	close (fd);
	return init_navalmap (mapType, mapSize, nbShips);
}
* */
size_t getFileSize(char * filename) {
	struct stat st;
	stat (filename, &st);	
	return st.st_size;
}
void read_input (char * filename) {
	info_t fic;
	char * map;
	int fd;
	size_t taille = getFileSize (filename);
	
	
	if ((fd = open (filename, O_RDONLY)) == -1)
		perror("opening file process failed");
		
		
	map = (char *)mmap (NULL, taille, PROT_READ, MAP_PRIVATE, fd, 0);
	printf ("%s\n" , map);
	
	
	munmap (map, taille);
	close(fd);
}

void initNavalMapLib () {
	srand (time (NULL) );
}

navalmap_t * init_navalmap (
	const map_t							mapType,
	const coord_t						mapSize,
	const int							nbShips) {
	navalmap_t							* nmap;
	int									j;
	nmap = malloc (sizeof (navalmap_t) );
	nmap->type = mapType;
	nmap->size = mapSize;
	nmap->nbShips = nbShips;
	nmap->shipPosition = malloc (nbShips * sizeof (coord_t) );
	for (j = 0; j < nbShips; ++j)
		nmap->shipPosition [j] .x = -1;
	nmap->map = malloc (mapSize.y * sizeof (entityid_t *) );
	for (j = 0; j < mapSize.y; ++j)
		nmap->map [j] = malloc (mapSize.x * sizeof (entityid_t) );

	switch (mapType) {
		case MAP_RECT:
			nmap->initEntityMap = rect_initEntityMap;
			nmap->isMovePossible = rect_isMovePossible;
			nmap->getTargets = rect_getTargets;
			break;
		default:
			printf ("Map type is not recognized. Type 'rectangle' is selected.\n");
			nmap->initEntityMap = rect_initEntityMap;
			nmap->isMovePossible = rect_isMovePossible;
			nmap->getTargets = rect_getTargets;
			break;
	}

	nmap->initEntityMap (nmap);

	return nmap;
}

void free_navalmap (
	navalmap_t							* nmap) {
	int									j;
	for (j = 0; j < nmap->size.y; ++j)
		free (nmap->map [j]);
	free (nmap->map);
	free (nmap->shipPosition);
	free (nmap);
}

void moveShip (
	navalmap_t							* nmap,
	const int							shipID,
	const coord_t						moveVec) {
	if (! nmap->isMovePossible (nmap, shipID, moveVec) ) return;

	nmap->map [nmap->shipPosition [shipID] .y][nmap->shipPosition [shipID] .x] .type = ENT_SEA;
	nmap->shipPosition [shipID] .x += moveVec.x;
	nmap->shipPosition [shipID] .y += moveVec.y;
	nmap->map [nmap->shipPosition [shipID] .y][nmap->shipPosition [shipID] .x] .type = ENT_SHIP;
	nmap->map [nmap->shipPosition [shipID] .y][nmap->shipPosition [shipID] .x] .id = shipID;
}

void placeRemainingShipsAtRandom (
	navalmap_t							* nmap) {
	int									i, j, k;
	for (k = 0; k < nmap->nbShips; ++k) {
		int								found = 0;

		if (nmap->shipPosition [k] .x != -1) continue;

		while (! found) {
			i = rand () % nmap->size.x;
			j = rand () % nmap->size.y;

			if (nmap->map [j][i] .type == ENT_SEA) found = 1;
		}

		nmap->shipPosition [k] .x = j;
		nmap->shipPosition [k] .y = i;
		nmap->map [j][i] .type = ENT_SHIP;
		nmap->map [j][i] .id = k;
	}
}

void placeShip (
	navalmap_t							* nmap,
	const int							shipID,
	const coord_t						pos) {
	if (shipID >= nmap->nbShips) return;
	if (pos.x < 0 || pos.x >= nmap->size.x || pos.y < 0 || pos.y >= nmap->size.y) return;

	if (nmap->map [pos.y][pos.x] .type == ENT_SHIP) {
		printf ("Placement for ship #%d is not possible.\n", shipID);
		return;
	}

	nmap->shipPosition [shipID] .x = pos.x;
	nmap->shipPosition [shipID] .y = pos.y;
	nmap->map [pos.y][pos.x] .type = ENT_SHIP;
	nmap->map [pos.y][pos.x] .id = shipID;
}
