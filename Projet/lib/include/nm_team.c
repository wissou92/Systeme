/*#include "nm_team.h"
#include "navalmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

int thread_function (int indice) {
	
	
}

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
	team_t * team1, team2;
	init_team (nmap, team1, team2);
	pid_t pid [2];
	int dscrpt_pere [2];
	int dscrpt_team [2][2];
	int i, j;
	
	for (i = 0; i<2; ++i) {
		pid [i] = fork ();
		
		if (pid [i] == -1) {
			printf ("fork error\n");
			exit (1);
			break;
		}
		else if (pid [i] == 0) {
			team_t team;
			if (i == 0) team = team1;
			else team = team2;
			
			pthread_t * thread = malloc (sizeof (pthread_t) * team-> nbJoueur); 
			close (dscrpt_pere [0]);
			close (dscrpt_team [i][1]);
			
			for (j = 0; j<team-> nbJoueur; ++j) {
				pthread_create (thread [j], NULL, thread_function (j), NULL);
			}
		}
		else {
			close (dscrpt_team [i][0]);
			
		}
		
	for (i = 0; i<1; ++i) {
		wait (NULL);
	}
}
*/
