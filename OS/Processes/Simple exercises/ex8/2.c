#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "header.h"

int main(int argc, char ** argv)
{

	int a2b, b2a;

	a2b = open("a2b", O_RDONLY);
	b2a = open("b2a", O_WRONLY);

	string current;

	while (1)
	{
		read(a2b, &current, sizeof(string));
	
		printf("%d", current.length);

		for (int i = 0 ; i < current.length ; i ++)
		{
			if (current.str[i] >= 'a' && current.str[i] <= 'z')
				current.str[i] = current.str[i] - 'a' + 'A';
		}
		write(b2a, &current, sizeof(string));	
	}

	close(a2b); close(b2a);

	return 0;
}

