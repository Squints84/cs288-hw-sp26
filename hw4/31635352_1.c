#include <stdio.h>
#include <stdlib.h>


int main() {
	int n;
	// int matrix1[100][100], matrix2[100][100], result_matrix[100][100];

	FILE* matrix_file_1;
	FILE* matrix_file_2;


	int dimension1;
	int dimension2;


	matrix_file_1 = fopen("matrix1.bin", "rb");
	fread(&dimension1, sizeof(int), 1, matrix_file_1);
	printf("dimension1: %d\n", dimension1);

	matrix_file_2 = fopen("matrix2.bin", "rb");
	fread(&dimension2, sizeof(int), 1, matrix_file_2);
	printf("dimension2: %d\n", dimension2);

	if (dimension1 != dimension2)
	{
		printf("The dimensions of each matrix are unequal.\nThus meaning that matrix multiplication is not possible.\nThe program will now exit.\n");
		exit(0);
	}

	if (dimension1 > 100 || dimension2 > 100)
	{
		printf("The dimensions of one of the matrices is too large to be mutiplied.\nThe program will now exit.\n");
		exit(0);
	}
	
	int *matrix1 = malloc(dimension1 * dimension1 * sizeof(int));
	int *matrix2 = malloc(dimension2 * dimension2 * sizeof(int));

	fread(matrix1, sizeof(int), dimension1 * dimension1, matrix_file_1);
	fread(matrix2, sizeof(int), dimension2 * dimension2, matrix_file_2);
	
	n = dimension1;

	int *result_matrix = calloc(n * n,  sizeof(int));
	
	if (result_matrix ==  NULL) {
	return 1;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int sum = 0;
			for (int k = 0; k < n; k++) {
				sum += matrix1[i * n + k] * matrix2[k * n + j];
			}
			result_matrix[i * n + j] = sum;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", result_matrix[i * n + j]);
		}
		printf("\n");
	}


	FILE *output_file = fopen("result.bin", "wb");

	printf("Writing result to result.bin\n");
	fwrite(&n, sizeof(int), 1,  output_file);
	fwrite(result_matrix, sizeof(int), n * n, output_file);
	fclose(output_file);

	free(matrix1);
	free(matrix2);
	free(result_matrix);
		
}


