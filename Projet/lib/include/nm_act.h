#include "navalmap.h"

// Un bateau utilise cette fonction pour détecter le bateau le plus proche de sa position
//\param							nmap			carte navale
//\param							shipID			ID du navire qui lance le radar
void radarscn (navalmap_t * nmap, const int shipID);

// Un bateau utilise cette fonction pour se réparer
//\param							nmap			carte navale
//\param							shipID			ID du navire
void reparation (navalmap_t * nmap, const int shipID);

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

// Un bateau utilise cette fonction pour charger
//\param							nmap			carte navale
//\param							shipID			ID du navire qui charge
//\param							moveVec			Vecteur dde la charge
void charge (navalmap_t * nmap, const int shipID, const coord_t mouv);

// Un bateau utilise cette fonction pour se déplacer
//\param							nmap			carte navale
//\param							shipID			ID du navire qui charge
//\param							cible			case d'arrivée
void charge (navalmap_t * nmap, const int shipID, const coord_t cible);

// Un bateau utilise cette fonction pour... ne rien faire
//\param							nmap			carte navale
//\param							shipID			ID du navire
void aucun (navalmap_t * nmap, const int shipID);

// Retourne la distance entre deux cases en "vecteur" (valeur absolue) entre deux cases
//\param							initial			case de départ
//\param							cible			case d'arrivée
//\return											distance entre 2 coordonnées
int getDistance (coord_t initial, coord_t cible);

