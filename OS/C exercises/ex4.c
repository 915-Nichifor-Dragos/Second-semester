#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

int i, j;
int *a;
int **mat;

FILE *in;
in = fopen(argv[1], "r");

a = (int*)malloc(2 * sizeof(int));

fscanf(in, "%d %d", &a[0], &a[1]);
printf("The matrix is %d by %d\n", a[0], a[1]);

mat = (int**)malloc(a[0] * sizeof(int*));
for (i = 0 ; i < a[0] ; i ++)
	mat[i] =(int*)malloc(a[1] * sizeof(int));

for (i = 0 ; i < a[0] ; i ++)
	for(j = 0 ; j < a[1] ; j ++)
		fscanf(in,"%d", &mat[i][j]);

printf("The matrix is the following:\n");

for(i = 0 ; i < a[0] ; i ++)
{
	for(j = 0 ; j < a[1] ; j ++)
	{
		printf("%d ", mat[i][j]);
	}
	printf("\n");
}

fclose(in);
for(i = 0 ; i < a[0] ; i ++)
	free(mat[i]);
free(a);
free(mat);

return 0;
}
