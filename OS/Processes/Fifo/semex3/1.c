#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char ** argv)
{
	int a2b, b2a, a, b;

	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	while (1)
	{
		printf("Please enter a and b with a space in between: ");
		scanf("%d", &a);
		scanf("%d", &b);

		write(a2b, &a, sizeof(int));
		write(a2b, &b, sizeof(int));
		
		int sum, prod;

		read(b2a, &sum, sizeof(int));
		read(b2a, &prod, sizeof(int));
		
		printf("The sum is: %d ; the product is: %d\n", sum, prod);

		if (sum == prod)
		{
			printf("\nFinished\n");
			break;
		}
		
	}

	close(a2b); close(b2a);

	return 0;
}


