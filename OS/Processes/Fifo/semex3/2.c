#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{
	int a2b, b2a, a, b;

	a2b = open("a2b", O_RDONLY);
	b2a = open("b2a", O_WRONLY);
	
	while(1)
	{
		read(a2b, &a, sizeof(int));
		read(a2b, &b, sizeof(int));

		int sum = a + b;
		int prod = a * b;

		write(b2a, &sum, sizeof(int));
		write(b2a, &prod, sizeof(int));

		if (sum == prod)
			break;
	}

	close(a2b); close(b2a);

	return 0;
}


