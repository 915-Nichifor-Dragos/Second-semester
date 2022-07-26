#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char ** argv)
{
	int a2b[2], b2a[2];

	int nr = -1;

	pipe(a2b); pipe(b2a);

	write(b2a[1], &nr, sizeof(int));

	if (fork() == 0) // A
	{
		close(a2b[0]); close(b2a[1]);

		while(1)
		{
			if(0 >= read(b2a[0], &nr, sizeof(int)))
			{
				break;
			}
			if (nr == 10)
			{
				printf("A - %d finished\n", nr);
				break;
			}
			printf("A - %d\n", nr);
			nr = random() % 10 + 1;
			write(a2b[1], &nr, sizeof(int));
		}
		close(a2b[1]); close(b2a[0]);
		exit(0);
	}

	if (fork() == 0) // B
	{
		close(a2b[1]); close(b2a[0]);

		while(1)
		{
			if(0 >= read(a2b[0], &nr, sizeof(int)))
			{
				break;
			}
			if (nr == 10)
			{
				printf("B - %d finished\n", nr);
				break;
			}
			printf("B - %d\n", nr);
			nr = random() % 10 + 1;
			write(b2a[1], &nr, sizeof(int));
		}
		close(a2b[0]); close(b2a[1]);
		exit(0);
	}


	else
	{
		wait(0);
		printf("\n\n APPLICATION FINISHED! \n\n");
	}

	return 0;
}


