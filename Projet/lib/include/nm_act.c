#include "nm_act.h"

void attaque (navalmap_t * nmap, const coord_t cible, const int shipID) {
	printf ("J%d -> ATK (%d, %d) ", shipID, cible.x, cible.y);
	nmap->
}

void mouvement (navalmap_t * nmap, const int shipID, const coord_t moveVec) {
	printf ("J%d -> MOV (%d, %d)", shipID, moveVec.x, moveVec.y);
	moveShip (nmap, shipID, moveVec);
}
