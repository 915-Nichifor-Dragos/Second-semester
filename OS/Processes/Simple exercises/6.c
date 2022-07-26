#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Please provide 1 argument\n");
		exit(1);
	}

	int n;

	n = atoi(argv[1]);

	int p2c[2], c2p[2], vector[n];

	pipe(p2c); pipe(c2p);

	int pid = fork();

	if (pid != 0)
	{
		close(p2c[0]); close(c2p[1]);
		for (int i = 0 ; i < n ; i ++)
			vector[i] = i;
		for (int i = 0 ; i < n ; i ++)
			if (0 > write(p2c[1], &vector[i], sizeof(int)))
				perror("Error on write");

		close (p2c[1]);
		float result;

		wait(0);

		if (0 > read(c2p[0], &result, sizeof(float)))
			perror("Error on read");
		close(c2p[0]);
		printf("The result is %f\n", result);
	}
	else
	{
		float sum = 0;
		float numbers = n;
		close(p2c[1]); close (c2p[0]);
		for (int i = 0 ; i < n ; i ++)
		{
			int nr;
			if (0 > read(p2c[0], &nr, sizeof(int)))
				perror("Error on read");
			sum += nr;
		}
		close(p2c[0]);
		float result = sum / numbers;
		if (0 > write(c2p[1], &result, sizeof(float)))
			perror("Error on write");
		close(c2p[1]);
		wait(0);
	}

	return 0;
}

