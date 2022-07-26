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
	char *s = "Hello!";

	f = open("a2b", O_WRONLY);

	n = strlen(s) + 1;

	write(f, &n, sizeof(int));
	write(f, s, n);

	close(f);

	return 0;
}


