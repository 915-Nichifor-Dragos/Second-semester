#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void f(int n)
{
	if (n <= 0)
		return;
	else
	{
		int pid = fork();
		if (pid == 0)
		{
			printf("Child: PID %d PPID %d FORK %d\n", getpid(), getppid(), pid);
			f(n - 1);
			exit(0);
		}
		wait(0);
	}
}

int main(int argc, char ** argv)
{
	f(3);
	return 0;
}

