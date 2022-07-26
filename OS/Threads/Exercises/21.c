#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Write a C program that creates 2^N threads that race to the finish (N is a command line argument). The threads must pass through N checkpoint. The checkpoint with number X will allow half as many threads to pass simultaneously than checkpoint number X - 1 (N >= X >=1). Checkpoint 0 (the first one) will allow 2^(N-1) to pass simultaneously through it.


typedef struct
{
	int index, N;
	pthread_barrier_t *barrier;
	sem_t *sems;
}data;


void *compute(void *argument)
{

	data arg = (*(data*)argument);

	pthread_barrier_wait(arg.barrier);
	printf("Thread %d is starting!\n", arg.index);

	for (int i = 0 ; i < arg.N ; i ++)
	{
		sem_wait(&arg.sems[i]);
		printf("Thread %d entered the checkpoint %d\n", arg.index, i);
		int time = (random() % 101 + 100) * 1000;
		usleep(time);
		sem_post(&arg.sems[i]);
	}

	printf("Thread %d has finished!\n", arg.index);

	return NULL;
}


int main (int argc, char ** argv)
{
	if (argc !=2)
	{
		printf("Enter a natural number N!\n");
		exit(1);
	}

	int N = atoi(argv[1]);

	int M = 1, ind = 0;

	while (ind <= N)
	{
		ind ++;
		M *= 2;
	}

	pthread_t *threads = malloc(sizeof(pthread_t) * M);
	sem_t *sems = malloc(sizeof(sem_t) * N);
	

	int step = 2;
	for (int i = 0 ; i < N ; i ++)
	{
		sem_init(&sems[i], 0, M / step);
		step *= 2;
	}

	pthread_barrier_t barrier;
	pthread_barrier_init(&barrier, NULL, M);

	data *args = malloc(sizeof(data) * M);

	for (int i = 0 ; i < M ; i ++)
	{
		args[i].N = N;
		args[i].index = i;
		args[i].barrier = &barrier;
		args[i].sems = sems;
		
		pthread_create(&threads[i], NULL, compute, (void*)&args[i]);
	}

	for (int i = 0 ; i < M ; i ++)
	{
		pthread_join(threads[i], NULL);
	}

	pthread_barrier_destroy(&barrier);

	for (int i = 0 ; i < N ; i ++)
	{
		sem_destroy(&sems[i]);
	}

	free(threads);
	free(args);
	free(sems);

	return 0;
}

