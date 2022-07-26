#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *f(void *a)
{
	printf("%d\n", *(int*)a);
	free(a);
	return NULL;
}

int main(int argc, char ** argv)
{
	pthread_t threads[100];

	for (int i = 0 ; i < 100 ; i ++)
	{
		int* p = malloc(sizeof(int));
		*p = i;
		pthread_create(&threads[i], NULL, f, p);
	}

	for (int i = 0 ; i < 100 ; i ++)
		pthread_join(threads[i], NULL);
	
	return 0;
}

