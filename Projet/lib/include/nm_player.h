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
//\param							distance		distance entre les deux navires
//\return 											un vecteur correspondant à un déplacement
coord_t vecteur_deplacement (coord_t ship_mv, coord_t cible, int distance);

// Detecte s'il y a un vainqueur ou non
//\param							nmap			carte navale
//\return											ID du vainqueur / -1 si pas de vainqueur / -2 plusieurs navire encore en jeu
int detecte_vainqueur (navalmap_t * nmap);

// Termine le programme en affichant le vainqueur s'il y en a
//\param							vainqueur		ID du vainqueur ou -1 s'il y en a pas
void game_over (int vainqueur);





