
void pere(pid_t a)
{
	sleep(3);
	kill(a, SIGSTOP);
	sleep(3);
	kill(a, SIGCOUNT);
}
lola<3
void fils()
{
	while
}

int main()
{
		pid_t a;
		if(a = fork()) pere(a);
		else fils();
		
		wait(NULL);
}
