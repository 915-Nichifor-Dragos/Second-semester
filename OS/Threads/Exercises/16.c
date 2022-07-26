#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int frequency[10];
pthread_mutex_t mutex;


void* doFrequency(void *a)
{
	int* number = (int*)a;

	while (*number)
	{
		int c = *number % 10;
		*number /= 10;
		pthread_mutex_lock(&mutex);
		frequency[c] ++;
		pthread_mutex_unlock(&mutex);	
	}

	free(number);
	return NULL;
}

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Please provide at least 1 argument\n");
		return 1;
	}

	pthread_t *threads = malloc(sizeof(pthread_t) * (argc - 1));

	for (int i = 0 ; i < argc - 1 ; i ++)
	{
		int* number = malloc(sizeof(int*));
		*number = atoi(argv[i]);

		pthread_create(&threads[i], NULL, doFrequency, (void*)number);
	}

	for (int i = 0 ; i <= 9 ; i ++)
	       printf("Digit %d has the frequency: %d\n", i, frequency[i]);	

	for (int i = 0 ; i < argc - 1 ; i ++)
		pthread_join(threads[i], NULL);

	free(threads);
	return 0;
}

