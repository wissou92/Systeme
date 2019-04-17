#include "navalmap.h"

// Algorithme du joueur
//\param							nmap			carte navale
void algorithme_decision (navalmap_t * nmap);

// Action du serveur suite au choix des joueurs
//\param							nmap			carte navale
//\param							shipID			ID du navire concerné
//\param							choix			choix du navire
//\param							arg				argument bonus pour certaine fonction
void choix_action (navalmap_t * nmap, const int shipID, int choix, void * arg);


// Renvoit un vecteur déplaçant un bateau vers un bateau cible
//\param							ship_mv			navire de base
//\param							cible			navire cible du navire de base
coord_t vecteur_deplacement (coord_t ship_mv, coord_t cible);


void game_over (int vainqueur);


int * elimination (navalmap_t * nmap);

int victoire (int * en_jeu, int nbShips);
