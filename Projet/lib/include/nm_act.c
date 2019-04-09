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

//					AUCUNE ACTION
void aucun (navalmap_t * nmap, const int shipID) {
	nmap-> shipInfo [shipID] .kerozene -= 1;
	printf ("J%d -> NON\n",shipID + 1);
}

 //					LES ATTAQUES
void attaque (navalmap_t * nmap, const int shipID, const coord_t cible) {
	nmap-> shipInfo [shipID] .kerozene -= 5;
	int i; int distance = getDistance (nmap-> shipPosition [shipID], cible);
	if (distance > 4 || distance < 2) {
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
	}
	
	if (nmap -> map [cible .x + 1][cible .y] .type == ENT_SHIP) { // a droite de la cible
		nmap-> shipInfo [nmap->map [cible .x + 1][cible .y] .id] . coque -= 20;
		printf ("J%d -> ATK (%d, %d) -> J%d subit 20C\n", shipID + 1, cible.x + 1, cible.y, nmap->map [cible .x + 1][cible .y] .id + 1);
	}
	if (nmap -> map [cible .x - 1][cible .y] .type == ENT_SHIP) { // a gauche de la cible
		nmap-> shipInfo [nmap->map [cible .x - 1][cible .y] .id] . coque -= 20;
		printf ("J%d -> ATK (%d, %d) -> J%d subit 20C\n", shipID + 1, cible.x - 1, cible.y, nmap->map [cible .x - 1][cible .y] .id + 1);
	}
	if (nmap -> map [cible .x][cible .y + 1] .type == ENT_SHIP) { // en haut de la cible
		nmap-> shipInfo [nmap->map [cible .x][cible .y + 1] .id] . coque -= 20;
		printf ("J%d -> ATK (%d, %d) -> J%d subit 20C\n", shipID + 1, cible.x, cible.y + 1, nmap->map [cible .x][cible .y + 1] .id + 1);
	}
	if (nmap -> map [cible .x][cible .y - 1] .type == ENT_SHIP) { // en bas de la cible
		nmap-> shipInfo [nmap->map [cible .x][cible .y - 1] .id] . coque -= 20;
		printf ("J%d -> ATK (%d, %d) -> J%d subit 20C\n", shipID + 1, cible.x, cible.y - 1, nmap->map [cible .x][cible .y - 1] .id + 1);
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
		printf ("J%d -> MOV (%d, %d)", shipID + 1, moveVec.x, moveVec.y);
	}
	else {
		printf ("Invalid movement\n");
	}
	//nmap->map [shipPosition [shipID] .x + moveVec.x][shipPosition [shipID] .y + moveVec.y] .type != ENT_SHIP
	//printf ("Invalid move\n");
}

//					LES RADARS
