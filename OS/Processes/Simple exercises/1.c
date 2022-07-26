#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*Write a C program that creates n child processes. Each child process will print its PID and its parent PID. The parent process will print its PID and the PID of each of the child processes.*/

int main(int argc, char ** argv)
{
	int pid;
	int n = 3;
	for (int i = 0; i < n ; i ++)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("C: Child PID %d Parent PPID %d\n", getpid(), getppid());
			exit(0);
		}
		else
			printf("P: Child PID %d Parent PID %d\n", pid, getpid());
	}

	for (int i = 0 ; i < n ; i ++)
		wait(0);

	printf("Message!\n");

	return 0;
}


