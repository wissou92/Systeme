#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void question1(int m, int n);
void question2(int m, int n);

int main()
{
	int n, m;
	printf("m = ?\n");
	scanf("%d", &m);
	printf("n = ?\n");
	scanf("%d", &n);
	question2(m, n);
	return 0;
}

void question1(int n, int m)
{
	pid_t pid;
	int status, nb_process=0;
	
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			pid = fork();
			if(pid == -1) //
			{
				exit(1);
			}
			else if(pid == 0) // Fils
			{
				printf("child pid: %d | parent pid: %d\n", getpid(), getppid());
				exit(2);
			}
			else // Pere
			{
				;
			}
		}
	}	
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			pid = wait(&status);
			nb_process += WEXITSTATUS(status);
			printf("child pid terminated: %d\n", pid);
		}
	}
	if(nb_process%2 ==0)
	printf("%d process created\n", nb_process/2);
	else
	printf("error during child process creation\n");
}

void question2(int m, int n)
{
	pid_t pid_p, pid_c;
	int descripteur[2];
	pipe(descripteur);
	
	int status, nb_process_p=0, nb_process_c=0;
	
	for(int i=0; i<m; i++)
	{
		pid_p = fork();
		
		switch(pid_p)
		{
			case -1: // Erreur création fils
				exit(1);
				break;
			case 0: // Fils
				printf("pid Fils: %d\n | pid Père: %d\n\n", getpid(), getppid());
				for(int j=0; j<n; j++)
				{
					pid_c = fork();
					if(pid_c == -1) // Erreur création petit-fils
					{
						exit(1);
					}
					else if(pid_c == 0) // Petit-fils
					{
						printf("pid Petit-Fils: %d\n | pid Fils (Père): %d\n\n", getpid(), getppid());
						exit(2);
					}
					else // Fils
					{
						
					}
				}
				for(int j=0; j<n; j++)
				{
					pid_c = wait(&status);
					printf("process child-child terminated: %d\n", pid_c);
					close(descripteur[0]);
					nb_process_c += WEXITSTATUS(status);
				}
				exit(2);
				break;
				
			default: // Père
				break;
		}
	}
	for(int i=0; i<m; i++)
	{
		pid_p = wait(&status);
		printf("process terminated: %d\n\n", pid_p);
		nb_process_p += WEXITSTATUS(status);
	}	
	close(descripteur[1]);
	read(descripteur[0], &nb_process_c, sizeof(int));
	if(nb_process_p%2 ==0 && nb_process_c%2==0)
	printf("nb de process enfant: %d,\nnb de process petits-enfants: %d\n", nb_process_p/2, nb_process_c/2);
}








