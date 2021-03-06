#include <stddef.h>
#ifndef _H_NAVALMAP_
#define _H_NAVALMAP_


// Pour stocker les informations provenant du fichier d'entrée dans une structure
typedef struct {
	char *		typeCarte;
	int			tailleX;
	int			tailleY;
	int			nbJoueurs;
	int			Cmax;
	int			Kmax;
	int			nbTours;
} info_t;

// Paire d'entiers représentant entre autre des coordonnées
typedef struct {
	int									x;					//< Premier entier
	int									y;					//< Second entier
} coord_t;

typedef struct {
	int temps;												//< "âge" du radar
	int distance;											//< Distance du bateau detecté
	int shipCoque;											//< Coque du bateau détecté
	int shipKerozene;										//< Kerozene du bateau détecté
	coord_t shipPos;										//< Coordonnées du bateau détecté
}radar_t;

// Structure représentant le bateau
typedef struct ship {
	int coque;												//< Pdv de la coque
	int kerozene;											//< Réservoir de kerozene
	radar_t radar;											//< radar 
	int en_vie;												//< Etat du navire pendant la partie (1 = en vie; 0 sinon);
	/*void (* aucun)			(struct navalmap *, const int);
												//< ne fait rien
	void (* mouvement)		(struct navalmap *, const int, const coord_t);
												//< se déplace
	void (* attaque)		(struct navalmap *, const int, const coord_t);
												//< attaquer
	void (* bombardier)		(struct navalmap *, const int, const coord_t);
												//< bombarder*/
} ship_t;

// Type de carte navale
typedef enum {
	MAP_RECT,												//< Carte rectangulaire avec bords
	MAP_TOTAL
} map_t;

// Type d'entité présente sur la carte navale
typedef enum {
	ENT_SEA,												//< Case maritime
	ENT_SHIP,												//< Case présentant un navire
	ENT_TOTAL
} entity_t;

// Entité
typedef struct {
	entity_t							type;				//< Type de l'entité
	int									id;					//< Identifiant de l'entité
} entityid_t;

// Carte navale
typedef struct navalmap {
	map_t								type;				//< Type de la carte
	coord_t								size;				//< Taille de la carte
	int									nbShips;			//< Nombre de navires (joueurs) sur la carte
	coord_t								* shipPosition;		//< Position des navires
	entityid_t							** map;				//< Carte des entités
	struct ship							* shipInfo;			//< Information sur les bateaux
	
	// Les pointeurs de fonctions peuvent être utilisés de la manière suivante :
	//	navalmap_t * nm;
	//	nm->initEntityMap (nm);
	//	nm->isMovePossible (nm, 4, pos);
	// Pour plus d'informations, reportez-vous aux définitions de ces fonctions dans les fichiers nm_*.h
	void (* initEntityMap) (struct navalmap *);				
															//< Fonction initialisant les entités présentes sur la carte
	int (* isMovePossible) (struct navalmap *, const int, const coord_t);
															//< Fonction indiquant si un mouvement est possible
	int * (* getTargets) (struct navalmap *, const coord_t, const int, int *);
															//< Fonction indiquant les entités situées à distance donnée d'une cible
} navalmap_t;

// Initialisation de la bibliothèque
// Génération de la graine aléatoire à partir de time()
void initNavalMapLib ();

// Initialisation d'une carte navale
// Création de la structure de la carte navale, les navires ne sont pas placés sur la carte
// \param								mapType				Type de la carte
// \param								mapSize				Taille de la carte
// \param								nbShips				Nombre de navires
// \return													Carte navale générée	
navalmap_t * init_navalmap (
	const map_t							mapType,
	const coord_t						mapSize,
	const int							nbShips);

// Suppression de la carte navale
// Désallocation de la mémoire utilisée par la structure de la carte navale
// \param								nmap				Carte à désallouer
void free_navalmap (
	navalmap_t							* nmap);

// Déplacement d'un navire sur la carte
// Le navire donné se déplace en fonction d'un vecteur (a, b), la nouvelle position devient donc (pos.x + a, pos.y + b)
// \param								nmap				Carte navale
// \param								shipID				Identifiant de navire
// \param								moveVec				Vecteur de déplacement
void moveShip (
	navalmap_t							* nmap,
	const int							shipID,
	const coord_t						moveVec);

// Place aléatoirement les navires non placés
// L'algorithme choisit aléatoirement une position, et vérifie qu'elle n'est pas déjà prise avant de l'affecter à un navire
// \param								nmap				Carte navale
void placeRemainingShipsAtRandom (
	navalmap_t							* nmap);

// Place un navire donné sur une position donnée
// Si le navire ne peut pas être placé à la position donnée, alors rien ne se passe
// \param								nmap				Carte navale
// \param								shipID				Identifiant de navire
// \param								pos					Position souhaitée du navire
void placeShip (
	navalmap_t							* nmap,
	const int							shipID,
	const coord_t						pos);
	
// Retourne la taille d'un fichier dont le nom est passé en paramètre
// \param								filename		nom du fichier
size_t getFileSize(char * filename);

// Remplit une structure en fonction des informations dans le fichier d'entrée passé en paramètre
// \param								filename		nom du fichier
// \return												structure contenant les informations du fichier
info_t read_input (char * filename);

// Initialise la carte navale en fonction de la structure contenant les informations nécessaires
// \param								fic				structure avec les informations
// \return												carte navale initialisée
navalmap_t * init_navalmap_wrapper (info_t fic);

// Initialise les navires et leur ressources en fonction des informations reçues du fichier d'entrée
// \param								nmap			carte navale
// \param								fic				structure contenant les informations du fichier d'entrée
void init_shipRessources (navalmap_t * nmap, info_t fic);

#include "nm_rect.h"
#include "nm_act.h"
#include "nm_player.h"
#include "nm_team.h"
#endif
