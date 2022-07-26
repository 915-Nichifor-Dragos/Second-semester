#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "1.h"
#include <fcntl.h>

int main(int argc, char ** argv)
{
	abc structure;

	int a2b = open("a2b", O_RDONLY);

	read(a2b, &structure, sizeof(abc));

	printf("The text: %s, the length %d", structure.string, structure.size);

	close(a2b);

	return 0;
}

