#include "nm_act.h"
#include "navalmap.h"
#include <stdio.h>

int getDistance (coord_t initial, coord_t cible) {
	coord_t moveVect;
	moveVect .x = initial .x - cible. x;
	if (moveVect .x < 0) moveVect .x = -(moveVect .x);
	moveVect .y = initial .y - cible .y;
	if (moveVect .y < 0) moveVect .y = -(moveVect .y);
	return (moveVect .x + moveVect .y);
}

void elimine (navalmap_t * nmap, const int shipID)
{
	if (nmap-> shipInfo [shipID] .coque <= 0 || nmap-> shipInfo [shipID] .kerozene <= 0)
	{
		nmap-> shipInfo [shipID] .en_vie = 0;
	}
}

//					AUCUNE ACTION
void aucun (navalmap_t * nmap, const int shipID) {
	nmap-> shipInfo [shipID] .kerozene -= 1;
	printf ("J%d -> NON\n",shipID + 1);
}

 //					LES ATTAQUES
void attaque (navalmap_t * nmap, const int shipID, const coord_t cible) {
	nmap-> shipInfo [shipID] .kerozene -= 5;
	int i; int distance = getDistance (nmap-> shipPosition [shipID], cible);
	
	if (cible .x > nmap-> size .x || cible .x < 0 ||
		cible .y > nmap-> size .y || cible .y < 0) {
		printf ("Invalid target\n");
		return;
	}
	else if ( distance < 2 || distance > 4) {
		printf ("Cible trop éloignée\n");
		return;
	}
	else if (nmap->map [cible .x][cible. y] .type == ENT_SEA) { 
		printf ("J%d -> ATK (%d, %d) -> Aucune cible touchée\n", shipID + 1, cible.x, cible.y);
	}
	else if (nmap->map [cible .x][cible .y] .type == ENT_SHIP) {
		nmap-> shipInfo [nmap->map [cible .x][cible .y] .id] . coque -= 40;
		printf ("J%d -> ATK (%d, %d) -> J%d subit 40C\n", shipID + 1, cible.x, cible.y, nmap->map [cible .x][cible .y] .id + 1);
		elimine (nmap, nmap->map [cible .x][cible .y] .id);
	}
	
	if (cible .x != nmap-> size .x)
	{
		if (nmap -> map [cible .x + 1][cible .y] .type == ENT_SHIP) { // a droite de la cible
			nmap-> shipInfo [nmap->map [cible .x + 1][cible .y] .id] . coque -= 20;
			printf ("J%d -> ATK (%d, %d) -> J%d subit 20C\n", shipID + 1, cible.x + 1, cible.y, nmap->map [cible .x + 1][cible .y] .id + 1);
			elimine (nmap, nmap->map [cible .x + 1][cible .y] .id);
		}
	}
	if (cible .x != 0)
	{
		if (nmap -> map [cible .x - 1][cible .y] .type == ENT_SHIP) { // a gauche de la cible
			nmap-> shipInfo [nmap->map [cible .x - 1][cible .y] .id] . coque -= 20;
			printf ("J%d -> ATK (%d, %d) -> J%d subit 20C\n", shipID + 1, cible.x - 1, cible.y, nmap->map [cible .x - 1][cible .y] .id + 1);
			elimine (nmap, nmap->map [cible .x - 1][cible .y] .id);
		}
	}
	if (cible .y != nmap-> size .y)
	{
		if (nmap -> map [cible .x][cible .y + 1] .type == ENT_SHIP) { // en haut de la cible
			nmap-> shipInfo [nmap->map [cible .x][cible .y + 1] .id] . coque -= 20;
			printf ("J%d -> ATK (%d, %d) -> J%d subit 20C\n", shipID + 1, cible.x, cible.y + 1, nmap->map [cible .x][cible .y + 1] .id + 1);
			elimine (nmap, nmap->map [cible .x][cible .y + 1] .id);
		}
	}
	if (cible .y != 0)
	{
		if (nmap -> map [cible .x][cible .y - 1] .type == ENT_SHIP) { // en bas de la cible
			nmap-> shipInfo [nmap->map [cible .x][cible .y - 1] .id] . coque -= 20;
			printf ("J%d -> ATK (%d, %d) -> J%d subit 20C\n", shipID + 1, cible.x, cible.y - 1, nmap->map [cible .x][cible .y - 1] .id + 1);
			elimine (nmap, nmap->map [cible .x][cible .y - 1] .id);
		}
	}
	
	
}

void bombardier (navalmap_t * nmap, const int shipID, const coord_t cible) {
	nmap -> shipInfo [shipID] .kerozene -= 3;
	int distance = getDistance (nmap-> shipPosition [shipID], cible);
	
	if (cible. x < 0 || cible .x >= nmap-> size .x
		|| cible .y < 0 || cible .y >= nmap-> size .y) {
		printf ("Invalid target\n");
	}
	else if (distance == 0 || distance  > 5) {
		printf ("Bombardement: cible invalide\n");
	}
	else if (nmap-> map [cible .x][cible .y] .id == ENT_SHIP) {
		nmap-> shipInfo [nmap-> map [cible .x][cible .y] .id] .coque -= 30;
		printf ("J%d -> BBS (%d, %d) -> J%d subit 30C\n", shipID + 1, cible .x, cible .y, nmap->map [cible .x][cible .y] .id + 1);
		elimine (nmap, nmap->map [cible .x][cible .y] .id);
	}
	else {
		printf ("J%d -> BBS (%d, %d) -> Aucune cible touchée\n", shipID + 1, cible.x, cible.y);
	}
}

//					LES MOUVEMENTS
void mouvement (navalmap_t * nmap, const int shipID, const coord_t moveVec) {
	nmap-> shipInfo [shipID] .kerozene -= 2;
	coord_t final; int distance;
	final .x = nmap-> shipPosition [shipID] .x + moveVec .x;
	final .y = nmap-> shipPosition [shipID] .y + moveVec .y;
	distance = getDistance (nmap-> shipPosition [shipID], final);
	if (distance == 0 || distance > 2) {
		printf ("Mouvement impossible\n");
	}
	else if (nmap->isMovePossible (nmap, shipID, moveVec) == 1) {
		moveShip (nmap, shipID, moveVec);
		printf ("J%d -> MOV (%d, %d)\n", shipID + 1, moveVec.x, moveVec.y);
	}
	else {
		printf ("Invalid movement\n");
	}
}

void charge (navalmap_t * nmap, const int shipID, const coord_t mouv) {
	nmap-> shipInfo [shipID] .kerozene -= 3;
	coord_t cible;
	cible .x = nmap-> shipPosition [shipID] .x + mouv .x;
	cible .y = nmap-> shipPosition [shipID] .y + mouv .y;
	int distance = getDistance (nmap-> shipPosition [shipID], cible);
	
	if (cible .x < 0 || cible .x > nmap-> size .x || cible .y < 0 || cible .y > nmap-> size .y) {
		printf ("Invalid charge\n");
		return;
	}
	else if ( (distance != 4 && distance != 5) || (cible .x != nmap-> shipPosition [shipID] .x && cible .y != nmap-> shipPosition [shipID] .y) ) {
		printf ("Charge impossible");
		return;
	}
	else if (nmap-> map [cible .x][cible .y] .type == ENT_SHIP) {
		nmap-> shipInfo [shipID] .coque -= 5;
		nmap-> shipInfo [nmap-> map [cible .x][cible .y] .id] .coque -= 50;
		moveShip (nmap, shipID, mouv);
		elimine (nmap, nmap->map [cible .x][cible .y] .id);
		printf ("J%d -> BST (%d, %d) -> J%d subit 5C et J%d subit 50C\n", shipID + 1, cible .x, cible .y, shipID + 1, nmap->map [cible .x][cible .y] .id + 1);
	}
	else {
		moveShip (nmap, shipID, mouv);
		printf ("J%d -> BST (%d, %d) -> Aucune cible touchée\n", shipID + 1, cible .x, cible .y);
	}
}

//					LES SOUTIENS
void radarscn (navalmap_t * nmap, const int shipID) {
	nmap-> shipInfo [shipID] .kerozene -= 3;
	printf ("J%d -> SCN\n", shipID + 1);
	int i, init, tmp;
	if (shipID == 0) init = 1;
	else init = 0;
	
	int ID = init;
	int distance = getDistance (nmap-> shipPosition [shipID], nmap-> shipPosition [init]);
	
	for (i=init + 1; i<nmap-> nbShips; ++i) {
		if (i == shipID) continue;
		tmp = getDistance (nmap-> shipPosition [shipID], nmap-> shipPosition [i]);
		if (tmp < distance) {
			 distance = tmp;
			 ID = i;
		}
	}
	nmap-> shipInfo [shipID] .radar .shipCoque = nmap-> shipInfo [ID] .coque;
	nmap-> shipInfo [shipID] .radar .shipKerozene = nmap-> shipInfo [ID] .kerozene;
	nmap-> shipInfo [shipID] .radar .shipPos = nmap-> shipPosition [ID];	
	nmap-> shipInfo [shipID] .radar .distance = distance;
	nmap-> shipInfo [shipID] .radar .temps = 0;
}

void reparation (navalmap_t * nmap, const int shipID) {
	nmap-> shipInfo [shipID] .kerozene -= 20;
	nmap-> shipInfo [shipID] .coque += 25;
	printf ("J%d -> RPR\n", shipID + 1);
}

