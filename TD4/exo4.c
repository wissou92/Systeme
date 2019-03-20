#include <unistd.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
 * 
 * clock_t times(struct tms *buf);
 * 
 * struct tms {
 * 	clock_t tms_utime; user time
 *  clock_t tms_stime; system time
 * 	clock_t tms_cutime; user time of children
 * 	clock_t tms_cstime; system time of children
 * }
 * */
int main(int argc, char** argv)
{
	struct tms buf;
	if(!fork())
	{
		system("ls -R");
		exit(1);
	}	
	wait(NULL);
	times(&buf);
	printf("%f\n", ((float)buf->tms_cutime/syscanf(_SC_CLK_TCK)) + ((float)buf->tms_cstime/sysscanf(_SC_CLK_TCK)));
}
