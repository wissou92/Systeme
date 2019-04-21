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

// Termine le programme en affichant le vainqueur s'il y en a
//\param							vainqueur		ID du vainqueur ou -1 s'il y en a pas
void game_over (int vainqueur);

// Rempli le tableau passé en paramètre avec des 0 (éliminé) ou 1 (en jeu) pour chaque navire
//\param							nmap			carte navale
//\param							tab				tableau à remplir
void joueur_restant (navalmap_t * nmap, int * tab);

// Detecte la situation actuel (1 gagnant, tous éliminé ou plusieur encore en jeu) et renvoit un code
// correspondant à la situation ou l'ID du navire gagnant
//\param							tab				tableau représentant les joueurs et leur situation
//\param							nbShips			nombre de navire en jeu
//\return											ID du vainqueur; ou -1 si pas de vainqueur; ou -2 si plusieurs navire encore en jeu
int detecte_vainqueur (int * tab, const int nbShips);



