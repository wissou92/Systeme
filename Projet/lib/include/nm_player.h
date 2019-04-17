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
