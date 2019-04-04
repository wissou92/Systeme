// Un bateau utilise cette fonction pour attaquer une case cible dans la carte
//\param							nmap			carte navale
//\param							cible			coordonnés de la case cible
//\param							shipID			ID du navire attaquant
void attaque (navalmap_t * nmap, const int shipID, const coord_t cible);

// Un bateau utilise cette fonction pour se déplacer
//\param							nmap			carte navale
//\param							shipID			ID du navire se déplaçant
//\param							moveVec			Vecteur du déplacement
void mouvement (navalmap_t * nmap, const int shipID, const coord_t moveVec);

// Retourne la distance entre deux cases en "vecteur" (valeur absolue) entre deux cases
//\param							initial			case de départ
//\param							cible			case d'arrivée
coord_t getDistance (coord_t initial, coord_t cible);
