#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{

int* k;
int* v;

if (argc < 2)
{
	printf("No file name\n");
	exit(1);
}

k = (int*)malloc(1 * sizeof(int));
FILE *in;
in = fopen(argv[1], "r");
fscanf(in, "%d", &k[0]);

printf("The number of elements is %d\n", k[0]);

v = (int*)malloc(k[0] * sizeof(int));

for(int i = 0 ; i < k[0] ; i ++)
	fscanf(in, "%d", &v[i]);

int sum = 0;

int i;
for(i = 0 ; i < k[0] ; i ++)
{
	sum += v[i];
	printf("%d ", v[i]);
}

printf("\n");
printf("%d", sum);
printf("\n");

fclose(in);
free(k);
free(v);

return 0;
}
