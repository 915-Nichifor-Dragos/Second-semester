#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{

	int a2b, b2a, n;

	a2b = open("a2b", O_RDONLY);
	b2a = open("b2a", O_WRONLY);

	srandom(getpid());

	while (1)
	{
		if(read(a2b, &n, sizeof(int)) <= 0)
			break;

		printf("B recieved: %d\n", n);

		if(n == 10)
		{
			printf("\nFinished\n");
			break;
		}
		else
		{
			n = random() % 10 + 1;
			printf("B sends: %d\n", n);
			write(b2a, &n, sizeof(int));
		}
	}

	close(a2b); close(b2a);

	return 0;
}

