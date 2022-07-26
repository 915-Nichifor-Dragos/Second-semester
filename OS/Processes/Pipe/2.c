#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char ** argv)
{
	int n = 25;
	int p2a[2], a2b[2], b2p[2];
	pipe(p2a); pipe(a2b); pipe(b2p);
	write(b2p[1], &n, sizeof(int));

	if (fork() == 0)
	{
		close(b2p[0]); close(b2p[1]);
		close(p2a[1]); close(a2b[0]);

		while (1)
		{
			if (read(p2a[0], &n, sizeof(int)) <= 0)
				break;
			if (n <= 0)
				break;
			printf("A: %d -> %d\n", n, n -1);
			n --;
			write(a2b[1], &n, sizeof(int));
		}
		close(p2a[0]); close(a2b[1]);
		exit (0);
	}

	if (fork() == 0)
	{
		close(p2a[0]); close(p2a[1]);
		close(a2b[1]); close(b2p[0]);

		while (1)
		{
			if (read(a2b[0], &n, sizeof(int)) <= 0)
				break;
			if (n <= 0)
				break;
			printf("B:%d -> %d\n", n, n - 1);
			n --;
			write(b2p[1], &n, sizeof(int));
		}
		close(a2b[0]); close(b2p[1]);
		exit(0);
	}

	close(a2b[0]); close(a2b[1]);
	close(b2p[1]); close(p2a[0]);

	while (1)
	{
		if (read(b2p[0], &n, sizeof(int)) <= 0)
			break;
		if (n <= 0)
			break;
		printf("P:%d -> %d\n", n, n - 1);
		n --;
		write(p2a[1], &n, sizeof(int));
	}
	close(p2a[1]); close(b2p[0]);
	wait(0); wait(0);

	return 0;
}

