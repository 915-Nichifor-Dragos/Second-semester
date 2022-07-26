#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char ** argv)
{
	int f, n;
	
	f = open("a2b", O_RDONLY);

	read(f, &n, sizeof(int));

	char *s = malloc(n);

	read(f, s, n);

	printf("%s with the length %d", s, n - 1);

	free(s);
	close(f);

	return 0;
}



