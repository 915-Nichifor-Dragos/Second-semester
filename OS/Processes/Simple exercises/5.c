#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int multiple_divisible_by_7(int nr)
{
	if (nr % 7 == 0)
		return 1;
	else
	{
		while(nr)
		{
			int c = nr % 10;
			nr /= 10;
			if (c == 7)
				return 1;
		}
	}
	return 0;
}

void play(int pipes[][2], int index, int n)
{
	int nr = 1, i;
	int read_idx = index % n;
	int write_idx = (index + 1) % n;
	for (i = 0 ; i < n ; i ++)
	{
		if (i == read_idx)
			close(pipes[read_idx][1]);
		else
			if (i == write_idx)
				close(pipes[write_idx][0]);
			else
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
	}
	if (index == 0)
	{
		printf("%d - start\n", nr);
		if ( 0 > write(pipes[write_idx][1], &nr, sizeof(int)))
			perror("Error on writing number");
	}
	while (nr >= 1)
	{
		if (0 > read(pipes[read_idx][0], &nr, sizeof(int)))
			perror("Error on reading number");
		if (nr != 0)
		{
			nr ++;
			int succes = random() % 3;
			if (multiple_divisible_by_7(nr))
			{
				if (! succes)
				{
					printf("%d - fail\n", nr);
					nr = 0;
				}
				else
					printf("Boltz!\n");
			}
			else
			{
				printf("%d\n", nr);
			}
			if (0 > write(pipes[write_idx][1], &nr, sizeof(int)))
				perror("Error writing on writing number");
		}
		else
		{
			if (0 > write(pipes[write_idx][1], &nr, sizeof(int)))
				perror("Error on writing number");
			break;
		}
	}
	wait(0);
	close(pipes[read_idx][0]);
	close(pipes[write_idx][1]);
}

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Please provide at least 1 argument\n");
		exit(1);
	}

	int n = 30, pipes[n][2], i;
	
	for (i = 0 ; i < n ; i ++)
	{
		pipe(pipes[i]);
	}

	for (i = 0 ; i < n ; i ++)
	{
		int pid = fork();
		if (pid > 0)
			break;
		else
		{

		}
	}
	if (i < n)
		play(pipes, i, n);

	return 0;
}


