#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int children[3];

void hp(int sgn)
{
	if (sgn == SIGUSR1)
	{
		printf("%d: Sending SIGUSR2 to child process.\n", getpid());
		for (int i = 0 ; i < 3 ; i ++)
		{
			kill(children[i], SIGUSR2);
		}
	}
	else
		if(sgn == SIGUSR2)
		{
			printf("%d: Sending SIGKILL to child process.\n", getpid());
			for (int i = 0 ; i < 3 ; i ++)
				kill(children[i], SIGKILL);
		}
}

void hc(int sgn)
{
	if (sgn == SIGUSR2)
	{
		printf("%d: Recieved SIGUSR2", getpid());
	}
}

int main(int argc, char ** argv)
{
	signal(SIGUSR1, hp);
	signal(SIGUSR2, hp);

	for (int i = 0 ; i < 3 ; i ++)
	{
		children[i] = fork();
		if (children[i] == 0)
		{
			while(1);
			exit(0);
		}
	}

	wait(0); wait(0); wait(0);

	return 0;
}

