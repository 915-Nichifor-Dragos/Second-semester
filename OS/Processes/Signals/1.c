#include <stdio.h>
#include <signal.h>

void f()
{
	printf("I don't want to stop.\n");
}

int main(int argc, char ** argv)
{
	signal(SIGINT, f);
	while(1);
	return 0;
}


