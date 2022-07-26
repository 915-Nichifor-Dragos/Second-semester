#include <stdio.h>
#include <pthread.h>

int n;

struct argt {
	int count;
	char* name;
};

void *f (void *a)
{
	struct argt* x = (struct argt*)a; 
	for(int i = 0 ; i < x->count ; i ++)
		printf("%s\n", x->name);
	return NULL;
}

int main(int argc, char ** argv)
{
	pthread_t ta, tb;

	if (argc < 1)
	{
		printf("Not enough arguments");
		return 1;
	}

	sscanf(argv[1], "%d", &n);

	struct argt sa, sb;
	sa.name = "fa";
	sa.count = n;
	sb.name = "fb";
	sb.count = n;

	pthread_create(&ta, NULL, f, &sa);
	pthread_create(&tb, NULL, f, &sb);

	for(int i = 0 ; i < n ; i ++)
		printf("main\n");

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	return 0;
}
