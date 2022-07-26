#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{

	int a2b = open("a2b", O_RDONLY);
	int b2a = open("b2a", O_WRONLY);
	int n;

	while (1)
	{
		read(a2b, &n, sizeof(int));
		n = n / 2;
		printf("B: %d diveded by two\n", n);
		write(b2a, &n, sizeof(int));
	}

	close(a2b); close(b2a);

	return 0;
}
