#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{

int **mat;
int rows, cols;
int i, j;
FILE *in;
in = fopen(argv[1], "r");
fscanf(in, "%d %d", &rows, &cols);

mat = (int**)malloc(rows * sizeof(int));
for(i = 0 ; i < rows ; i ++)
	mat[i] = (int*)malloc(cols * sizeof(int));

for (i = 0 ; i < rows ; i ++)
	for (j = 0 ; j < cols ; j ++)
		fscanf(in, "%d", &mat[i][j]);

for(i = 0 ; i < rows ; i ++)
{
	for(j = 0 ; j < cols ; j ++)
	{
		printf("%d ", mat[i][j]);
	}
	printf("\n");
}

fclose(in);
for (i = 0 ; i < rows ; i ++)
	free(mat[i]);
free(mat);

return 0;
}
