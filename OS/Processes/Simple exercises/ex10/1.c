#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{

	int a2b = open("a2b", O_WRONLY);
	int b2a = open("b2a", O_RDONLY);

	int n;
	srandom(getpid());
	n = random() % 151 + 50;
	
	write(a2b, &n, sizeof(int));

	while (1)
	{
		read(b2a, &n, sizeof(int));
		printf("A: %d\n", n);
		if (n < 5)
			break;
		if (n % 2 == 0)
			write(a2b, &n, sizeof(int));
		else
		{
			n ++;
			write(a2b, &n, sizeof(int));
		}
	}

	close(a2b); close(b2a);

	return 0;
}

