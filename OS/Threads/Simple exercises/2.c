#include <stdio.h>
#include <pthread.h>

int n;

void *fa (void *a)
{
	int i;
	for (i = 0 ; i < n ; i ++)
	       printf("fa\n");
	return NULL;	
}


void *fb(void *a)
{
	int i;
	for (i = 0 ; i < n ; i ++)
		printf("fb\n");
	return NULL;
}


int main (int argc, char ** argv)
{
	if (argc < 1)
	{
		printf("Not enough arguments\n");
		return 1;
	}

	sscanf(argv[1], "%d", &n);

	pthread_t a, b;

	pthread_create(&a, NULL, fa, NULL);
	pthread_create(&b, NULL, fb, NULL);

	for (int i = 0 ; i < n ; i ++)
		printf("main\n");

	pthread_join(a, NULL);
	pthread_join(b, NULL);
}
