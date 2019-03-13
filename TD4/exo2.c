#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() 
{
	pid_t a;
	int i;
	
	srand(time(NULL)):
	
	for(i=0; i<10; i++)
	{
		int s = 1+(rand()%10);
		if(!fork())
		{
			sleep(s);
			printf("%d\n", getpid());
			exit(0);
		}
	}
	for(i=0; i<10; i++)
	{
		a = wait(NULL);
		printf("%d est fini\n", a);
	}
	return 0;
}
