#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/* Write a program that receives strings of characters as command line arguments. For each string the program creates a thread which calculates the number of digits, the number of leters and the number of special characters (anything other than a letter or digit). The main program waits for the threads to terminate and prints the total results (total number of digits, letters and special characters across all the received command line arguments) and terminates. Use efficient synchronization. Do not use global variables */

typedef struct {

	int *numbers, *letters, *specials;
	pthread_mutex_t *mutexes;
	char *str;

}data;


void *function (void *arg)
{
	int l = 0, s = 0, n = 0;
	data dt = *((data*)arg);
	for (int i = 0 ; i < strlen(dt.str) ; i ++)
	{
		if ((dt.str[i] >= 'a' && dt.str[i] <= 'z') || (dt.str[i] >= 'A' && dt.str[i] <= 'Z'))
			l ++;
		else 
			if (dt.str[i] >= '0' && dt.str[i] <= '9')
				n ++;
			else
				s ++;
	}

	if (l > 0)
	{
		pthread_mutex_lock(&dt.mutexes[0]);
		*(dt.letters) += l;
		pthread_mutex_unlock(&dt.mutexes[0]);
	}
	if (n > 0)
	{
		pthread_mutex_lock(&dt.mutexes[1]);
		*(dt.numbers) += n;
		pthread_mutex_unlock(&dt.mutexes[1]);
	}
	if (s > 0)
	{
		pthread_mutex_lock(&dt.mutexes[2]);
		*(dt.specials) += s;
		pthread_mutex_unlock(&dt.mutexes[2]);
	}
	
	return NULL;
}


int main (int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("No arguments given.\n");
		return 1;
	}
	int *letters = malloc(sizeof(int));
	int *specials = malloc(sizeof(int));
	int *numbers = malloc(sizeof(int));

	pthread_t *threads = malloc(sizeof(pthread_t) * (argc - 1));
	data *args = malloc(sizeof(data) * (argc - 1));
	pthread_mutex_t *mutexes = malloc(sizeof(pthread_mutex_t) * 3);

	for (int i = 0 ; i < 3 ; i ++)
	{
		pthread_mutex_init(&mutexes[i], NULL);
	}

	*letters = 0;
	*specials = 0;
	*numbers = 0;

	for (int i = 0 ; i < argc - 1 ; i ++)
	{
		args[i].letters = letters;
		args[i].specials = specials;
		args[i].numbers = numbers;
		args[i].mutexes = mutexes;
		args[i].str = argv[i + 1];
		pthread_create(&threads[i], NULL, function, (void*) &args[i]);
	}

	for (int i = 0 ; i < argc - 1 ; i ++)
	{
		pthread_join(threads[i], NULL);
	}

	for (int i = 0 ; i < 3 ; i ++)
	{
		pthread_mutex_destroy(&mutexes[i]);
	}

	printf("Letters %d, digits %d, specials %d", *letters, *numbers, *specials);

	free(letters);
	free(numbers);
	free(specials);
	free(args);
	free(mutexes);
	free(threads);

	return 0;
}

