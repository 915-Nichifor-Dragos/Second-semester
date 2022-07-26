#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


// Create a C program that converts all lowecase letters from the command line arguments to uppercase letters and prints the result. Use a thread for each given argument.


typedef struct {
	char str[100];
}data;


void *compute(void *arg)
{
	data argument = *((data*)arg);
	for (int i = 0 ; i < strlen(argument.str) ; i ++)
	{
		if (argument.str[i] >= 'a' && argument.str[i] <= 'z')
			argument.str[i] = argument.str[i] - 'a' + 'A';
	}	

	printf ("%s ", argument.str);

	return NULL;
}


int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Please provide at least 1 argument!\n");
		return 1;
	}

	pthread_t *threads = malloc(sizeof(pthread_t) * argc);
	data *arguments = malloc(sizeof(data) * argc);

	for (int i = 0 ; i < argc ; i ++)
	{
		strcpy(arguments[i].str, argv[i]);
		pthread_create(&threads[i], NULL, compute, (void*)&arguments[i]);
	}

	for (int i = 0 ; i < argc ; i ++)
		pthread_join(threads[i], NULL);

	free (threads);
	free (arguments);
	
	return 0;
}

