#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int f;

void parent_handler(int sig)
{
	printf("Terminating parent process\n");
	kill(f, SIGUSR1);
	wait(0);
	exit(0);
}


void child_handler(int sig)
{
	printf("Terminating child process\n");
	exit(0);
}


void zombie_handler(int sig)
{
	printf("Parent waiting for child to terminate\n");
	wait(0);
}


int main(int argc, char ** argv)
{
	f = fork();
	if(f == 0)
	{
		signal(SIGUSR1, child_handler);
		printf("C - CHILD PID: %d PARENT PID: %d\n", getpid(), getppid());
		while(1)
		{
			printf("Child working...\n");
			sleep(2);
		}
		exit(0);
	}
	else
	{
		signal(SIGCHLD, zombie_handler);
		signal(SIGUSR1, parent_handler);
		printf("P - PARENT PID: %d CHILD PID %d\n", getpid(), f);
		while(1)
		{
			printf("Parent working...\n");
			sleep(2);
		}
	}
	return 0;
}

