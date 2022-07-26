#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Please enter at least 1 argument.\n");
		exit(1);
	}

	int pid = fork();
	
	if (pid == 0)
	{
		execvp(argv[1], argv + 1);
		exit(0);
	}

	wait(0);
	printf("\n\nGREP WORKED!\n\n");

	return 0;
}

