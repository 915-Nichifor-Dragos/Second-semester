#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char ** argv)
{
	int a2b[2], b2a[2];

	pipe(a2b); pipe(b2a);

	int pid = fork();

	if (pid > 0)
	{
		close(a2b[0]); close(b2a[1]);
		
		while (1)
		{
			int a, b;
			printf("Please enter a and b with a space in between: ");
			scanf("%d", &a);
			scanf("%d", &b);

			write(a2b[1], &a, sizeof(int));
			write(a2b[1], &b, sizeof(int));

			int sum, prod;

			read(b2a[0], &sum, sizeof(int));
			read(b2a[0], &prod, sizeof(int));

			printf("SUM: %d ; PRODUCT %d\n", sum, prod);

			if (sum == prod)
			{
				wait(0);
				break;
			}
		}
		
		close(a2b[1]); close(b2a[0]);

	}
	else
		if(pid == 0)
		{

			close(a2b[1]); close(b2a[0]);

			while (1)
			{
				int a, b;
				int sum, prod;

				read(a2b[0], &a, sizeof(int));
				read(a2b[0], &b, sizeof(int));

				sum = a + b;
				prod = a * b;

				write(b2a[1], &sum, sizeof(int));
				write(b2a[1], &prod, sizeof(int));

				if(sum == prod)
					exit(0);
			}
			
			close(a2b[0]); close(b2a[1]);
		}

	return 0;
}

