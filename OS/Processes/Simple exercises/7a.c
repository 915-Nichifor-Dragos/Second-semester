#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char ** argv)
{

	int a2b, b2a, n;

	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	n = random() % 10 + 1;
	write(a2b, &n, sizeof(int));

	srandom(getpid());

	while (1)
	{
		if (read(b2a, &n, sizeof(int)) <= 0)
			break;

		printf("A recieved: %d\n", n);

		if (n == 10)
		{
			printf("\nFinished\n");
			break;
		}
		else
		{
			n = random() % 10 + 1;
			printf("A sends: %d\n", n);
			write(a2b, &n, sizeof(int));
		}
	}

	close(a2b); close(b2a);

	return 0;

}


