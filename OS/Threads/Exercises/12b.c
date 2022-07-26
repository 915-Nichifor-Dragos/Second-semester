#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int rows, columns;
int* sum;
pthread_mutex_t mutex;

void *add_elements(void *args)
{
	int* a = (int*)args;
	int current_sum = 0;
	for (int i = 0 ; i < columns ; i ++)
		current_sum += a[i];

	pthread_mutex_lock(&mutex);
	*sum = *sum + current_sum;
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main (int argc, char ** argv)
{
	sum = malloc(sizeof(int));
	*sum = 0;
	FILE* file;
	file = fopen("matrix2.txt", "r");

	fscanf(file, "%d", &rows);
	fscanf(file, "%d", &columns);

	int** a = (int**)malloc(sizeof(int*) * rows);

	for (int i = 0 ; i < rows ; i ++)
		a[i] = (int*)malloc(sizeof(int) * columns);

	for (int i = 0 ; i < rows ; i ++)
		for (int j = 0 ; j < columns ; j ++)
			fscanf(file, "%d", &a[i][j]);

	pthread_t* threads = malloc(sizeof(pthread_t) * rows);
	pthread_mutex_init(&mutex, NULL);

	for (int i = 0 ; i < rows ; i ++)
		pthread_create(&threads[i], NULL, add_elements, (void*)a[i]);

	for (int i = 0 ; i < rows ; i ++)
		pthread_join(threads[i], NULL);

	printf("The sum is: %d\n", *sum);

	for (int i = 0 ; i < rows ; i ++)
	{
		free(a[i]);
	}

	free(a);
	free(threads);
	fclose(file);
	free(sum);

	return 0;
}

