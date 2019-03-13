#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {
	int status;
	int alea;
	
	int descripteur[2];
	if(pipe(descripteur) != 0){
		return EXIT_FAILURE;
	}
	
	pid_t pid = fork();
	
	switch(pid) {
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0: // Processus Fils
			alea = (rand()%50)+1;
			printf("Le fils choisit ce chiffre : %d\n", alea);
			close(descripteur[0]);
			write(descripteur[1], &alea, sizeof(int)); 
			exit(2);
			break;
		default: // Processus Pere
			close(descripteur[1]);
			read(descripteur[0], &alea, sizeof(int));
			wait(&status);
			if(WIFEXITED(status)){
				printf("Le pere affiche ce chiffre : %d\n", alea);
			}
			else {
				
			}
	}
	
	return 0;
}
