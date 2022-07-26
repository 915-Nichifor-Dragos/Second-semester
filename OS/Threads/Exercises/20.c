#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


typedef struct {

	int index, M;
	pthread_mutex_t *mutexes;
	pthread_barrier_t *barrier;

}data;


void *compute(void* argument)
{
	data arg = (*(data*)argument);
	printf("Thread %d is waiting\n", arg.index);
	pthread_barrier_wait(arg.barrier);

	for (int i = 0 ; i < arg.M ; i ++)
	{
		pthread_mutex_lock(&arg.mutexes[i]);
		printf("Thread %d has entered the checkpoint %d\n", arg.index, i);
		int time = (random() % 101 + 100) * 1000;
		usleep(time);
		
		pthread_mutex_unlock(&arg.mutexes[i]);
		printf("Thread %d has exited the checkpoint %d\n", arg.index, i);
	}
	printf("Thread %d has finished\n", arg.index);

	return NULL;
}


int main (int argc, char ** argv)
{
	if (argc != 3)
	{
		printf("Please provide 2 arguments: N and M\n");
		exit(1);
	}

	int N = atoi(argv[1]);
	int M = atoi(argv[2]);

	pthread_t *threads = malloc(N * sizeof(pthread_t));
	pthread_mutex_t *mutexes = malloc(M * sizeof(pthread_mutex_t));
	data *args = malloc(N * sizeof(data));

	pthread_barrier_t barrier;

	pthread_barrier_init(&barrier, NULL, N);

	for (int i = 0 ; i < M ; i ++)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		// pthread_mutex_unlock(&mutexes[i]);
	}

	for (int i = 0 ; i < N ; i ++)
	{
		args[i].index = i;
		args[i].M = M;
		args[i].mutexes = mutexes;
		args[i].barrier = &barrier;

		pthread_create(&threads[i], NULL, compute, (void*)&args[i]);
	}


	for(int i = 0 ; i < N ; i ++)
	{
		pthread_join(threads[i], NULL);
	}

	for (int i = 0 ; i < M ; i ++)
	{
		pthread_mutex_destroy(&mutexes[i]);
	}

	pthread_barrier_destroy(&barrier);

	free(args);
	free(threads);
	free(mutexes);


	return 0;
}
