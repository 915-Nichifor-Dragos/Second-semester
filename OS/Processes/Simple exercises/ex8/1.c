#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include "header.h"

int main(int argc, char ** argv)
{

	int a2b, b2a;

	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	if (argc < 2)
	{
		printf("Please enter at least one argument\n");
		close(a2b); close(b2a);
		exit(1);
	}

	char result[1000];
	result[0] = '\0';

	for (int i = 1 ; i < argc ; i ++)
	{
		string current;
		strcpy(current.str, argv[i]);
		current.length = strlen(current.str);
		write(a2b, &current, sizeof(string));
		if(0 >= read(b2a, &current, sizeof(string)))
		       break;
		printf("string: %s; size %d\n", current.str, current.length);

		strcat(result, current.str);
		strcat(result, " ");
	}

	close(a2b); close(b2a);

	printf("%s\n", result);

	return 0;
}

