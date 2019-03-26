#include "navalmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

navalmap_t * read_fileInput (char * fileName) {
	int fd = open(fileName, O_RDONLY);
	/*if (fd == -1) {
		
	}*/
	char lignes[100];
	read (fd, ligne, 100);
	
	navalmap_t * naval_map = init_navalmap ( );
	close (fd);
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
