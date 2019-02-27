#include "se_fichier.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

SE_FICHIER SE_ouverture (const char * chemin, int acces) {
	SE_FICHIER fichier;
	fichier.chemin = malloc(256*sizeof(char));
	int fd = open(chemin, acces | O_CREAT, 0744);
	if(fd == -1) {
		fprintf(stderr, "erreur ouverture/création du fichier\n");
		exit(EXIT_FAILURE);
	} else {
		fichier.descripteur = fd;
		strcpy(fichier.chemin, chemin);
		fichier.acces = acces;
	}
	return fichier;
}

int SE_fermeture (SE_FICHIER fichier) {
	return (close(fichier.descripteur)==0) ? 1 : 0;
}

int SE_suppression (const char * chemin) {
	return (remove(chemin)==0) ? 1 : 0;
}

int SE_lectureCaractere (SE_FICHIER fichier, char * caractere) {
	switch(fichier.acces) {
		case(O_RDONLY):
			read(fichier.descripteur, caractere, 1);
			break;
		case(O_RDWR):
			read(fichier.descripteur, caractere, 1);
			break;
		default:
			fprintf(stderr, "Permission non-accordée\n");
			break;
	}
}

int SE_ecritureCaractere (SE_FICHIER fichier, const char caractere) {
	switch(fichier.acces) {
		case(O_WRONLY):
			write(fichier.descripteur, &caractere, 1);
			break;
		case(O_RDWR):
			write(fichier.descripteur, &caractere, 1);
			break;
		default:
			fprintf(stderr, "Permission non-accordée\n");
			break;
	}
}
