#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "1.h"

int main(int argc, char ** argv)
{
	abc structure;

	int a2b = open("a2b", O_WRONLY);

	strcpy(structure.string, "Hello!");
	structure.size = strlen(structure.string);

	write(a2b, &structure, sizeof(abc));

	close(a2b);

	return 0;
}

