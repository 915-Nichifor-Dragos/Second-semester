#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {

	int n;
	int* index;
	int* array;
	pthread_mutex_t *mutex;
	pthread_cond_t *cond;

}data;


void *compute1(void *arg)
{
	data argument = (*(data*)arg);

	pthread_mutex_lock(argument.mutex);
	while(*argument.index < argument.n && *argument.index % 2 != 0)
		pthread_cond_wait(argument.cond, argument.mutex);

	while (*argument.index < argument.n)
	{
		int nr = (random() % 51) * 2;

		argument.array[*argument.index] = nr;
		*argument.index += 1;
		printf("F1: %d\n", nr);
		pthread_cond_signal(argument.cond);

		while (*argument.index < argument.n && *argument.index % 2 != 0)
			pthread_cond_wait(argument.cond, argument.mutex);

	}

	pthread_cond_signal(argument.cond);
	pthread_mutex_unlock(argument.mutex);

	return NULL;
}

void *compute2(void *arg)
{
	data argument = (*(data*)arg);
	pthread_mutex_lock(argument.mutex);
	while(*argument.index < argument.n && *argument.index % 2 != 1)
		pthread_cond_wait(argument.cond, argument.mutex);

	while(*argument.index < argument.n)
	{
		int nr = (random() % 51) * 2 + 1;
		argument.array[*argument.index] = nr;
		*argument.index += 1;
		printf("F2:%d\n", nr);
		pthread_cond_signal(argument.cond);

		while(*argument.index < argument.n && *argument.index % 2 != 1)
			pthread_cond_wait(argument.cond, argument.mutex);
	}

	pthread_cond_signal(argument.cond);
	pthread_mutex_unlock(argument.mutex);

	return NULL;
}


int main (int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Please provide a natural number n\n");
		return 1;
	}

	int n = atoi(argv[1]);
	int *arr = malloc(sizeof(int) * n);
	int index = 0;

	pthread_t *threads = malloc(sizeof(pthread_t) * 2);
	pthread_mutex_t mutex;
	pthread_cond_t cond;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	data *args = malloc(2 * sizeof(data));	
	
	args[0].n = n;
	args[0].array = arr;
	args[0].mutex = &mutex;
	args[0].cond = &cond;
	args[0].index = &index;

	args[1].n = n;
	args[1].array = arr;
	args[1].mutex = &mutex;
	args[1].cond = &cond;
	args[1].index = &index;

	pthread_create(&threads[0], NULL, compute1, (void*)&args[0]);
	pthread_create(&threads[1], NULL, compute2, (void*)&args[1]);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	for (int i = 0 ; i < n ; i ++)
		printf("%d ", arr[i]);

	free(threads);
	free(args);
	free(arr);

	return 0;
}

