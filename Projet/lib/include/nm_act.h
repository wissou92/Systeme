#include "navalmap.h"

// Un bateau utilise cette fonction pour attaquer une case cible dans la carte
//\param							nmap			carte navale
//\param							cible			coordonnés de la case cible
//\param							shipID			ID du navire attaquant
void attaque (navalmap_t * nmap, const int shipID, const coord_t cible);

// Un bateau utilise cette fonction pour bombarder une case cible
//\param							nmap			carte navale
//\param							cible			coordonnés de la case cible
//\param							shipID			ID du navire attaquant
void bombardier (navalmap_t * nmap, const int shipID, const coord_t cible);

// Un bateau utilise cette fonction pour se déplacer
//\param							nmap			carte navale
//\param							shipID			ID du navire se déplaçant
//\param							moveVec			Vecteur du déplacement
void mouvement (navalmap_t * nmap, const int shipID, const coord_t moveVec);

// Un bateau utilise cette fonction pour... ne rien faire
//\param							nmap			carte navale
//\param							shipID			ID du navire
void aucun (navalmap_t * nmap, const int shipID);

// Retourne la distance entre deux cases en "vecteur" (valeur absolue) entre deux cases
//\param							initial			case de départ
//\param							cible			case d'arrivée
int getDistance (coord_t initial, coord_t cible);

