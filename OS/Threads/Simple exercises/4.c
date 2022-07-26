#include <stdio.h>
#include <pthread.h>

int count = 0;

void *f (void *a)
{
	for (int i = 0 ; i < *(int*)a; i ++)
		count ++;
	return NULL;
}

int main(int argc, char ** argv)
{
	pthread_t threads[10];

	if (argc <= 1)
	{
		printf("Not enough arguments\n");
		return 1;
	}

	int n;

	sscanf(argv[1], "%d", &n);

	for (int i = 0 ; i < 10 ; i ++)
		pthread_create(&threads[i], NULL, f, &n);

	for (int i = 0 ; i < 10 ; i ++)
		pthread_join(threads[i], NULL);
	
	printf ("%d\n", count);

	return 0;
}

