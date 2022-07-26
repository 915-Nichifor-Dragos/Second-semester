#include <stdio.h>
#include <pthread.h>

void *f (void *a)
{
	printf ("%d\n", *(int*)a);
	return NULL;
}

int main(int argc, char ** argv)
{
	int a[100];
	pthread_t threads[100];

	for (int i = 0 ; i < 100 ; i ++)
	{
		a[i] = i;
		pthread_create(&threads[i], NULL, f, &a[i]);
	}

	for (int i = 0 ; i < 100 ; i ++)
		pthread_join(threads[i], NULL);

	return 0;
}
