#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

void f()
{
	printf("There is no point to wait for me... I will destroy my process alone.\n");
	wait(0);
}

void g()
{
	int command;
	printf("Are you sure you want to quit?[1-yes/0-no]\n");
	scanf("%d", &command);
	if (command == 1)
		exit(0);
}

int main(int argc, char ** argv)
{
	signal(SIGINT, g);
	signal(SIGCHLD, f);
	for (int i = 0 ; i < 3 ; i ++)
	{
		int pid = fork();
		if (pid == 0)
		{
			printf("I am child proces PID %d PIDD %d.\n", getpid(), getppid());
			exit(0);
		}
	}
	while(1);
	return 0;
}

