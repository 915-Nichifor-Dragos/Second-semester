#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
if (argc < 2)
{
	printf("Not enough arguments\n");
	exit(1);
}

int i;

for (i = 1 ; i < argc ; i ++)
	printf("The argument no. %d is %s\n", i, argv[i]);

return 0;
}
