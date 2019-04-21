#include "nm_team.h"
#include "navalmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void init_team (navalmap_t * nmap, team_t * team1, team_t * team2) {
	int i;
	
	team1-> nbJoueur = (nmap-> nbShips)/2;
	if (nmap-> nbShips % 2 != 0) team1-> nbJoueur++;
	team1-> teamID = malloc (sizeof (int) * team1-> nbJoueur);
	team2-> nbJoueur = team1-> nbJoueur;
	team2-> teamID = malloc (sizeof (int) * team2-> nbJoueur);
	
	for (i = 0; i<nmap-> nbShips; ++i) {
		if (i < team1-> nbJoueur) team1-> teamID[i] = i;
		else team2-> teamID[i%(team1-> nbJoueur)] = i;
	}
}

void free_team (team_t * team1, team_t * team2) {
	free (team1-> teamID); free (team2-> teamID);
}

void deathmatch (navalmap_t * nmap) {
	
}
