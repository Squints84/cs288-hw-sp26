#include <stdio.h>
#include <stdlib.h>

int main() {
	int exit_code = 1;

	FILE *input_file1 = NULL;
	FILE *input_file2 = NULL;
	FILE *output_file = NULL;

	int rows1 = 0;
	int nonzeros1 = 0;

	int rows2 = 0;
	int nonzeros2 = 0;

	int *values1 = NULL;
	int *column_indices1 = NULL;
	int *row_start1 = NULL;

	int *values2 = NULL;
	int *column_indices2 = NULL;
	int *row_start2 = NULL;

	int num_rows = 0;
	int result_nonzeros = 0;

	int *result_values = NULL;
	int *result_column_indices = NULL;
	int *result_row_start = NULL;

	input_file1 = fopen("sparse_matrix1.txt", "r");
	if (input_file1 == NULL) {
		printf("Failed to open sparse_matrix1.txt\n");
		goto cleanup;
	}

	input_file2 = fopen("sparse_matrix2.txt", "r");
	if (input_file2 == NULL) {
		printf("Failed to open sparse_matrix2.txt\n");
		goto cleanup;
	}

	/* read first matrix */
	if (fscanf(input_file1, "%d", &rows1) != 1) {
		printf("Failed to read number of rows for first matrix\n");
		goto cleanup;
	}
	if (fscanf(input_file1, "%d", &nonzeros1) != 1) {
		printf("Failed to read number of non-zero elements for first matrix\n");
		goto cleanup;
	}

	values1 = malloc(nonzeros1 * sizeof(int));
	column_indices1 = malloc(nonzeros1 * sizeof(int));
	row_start1 = malloc((rows1 + 1) * sizeof(int));

	if (values1 == NULL || column_indices1 == NULL || row_start1 == NULL) {
		printf("Memory allocation failed for first matrix\n");
		goto cleanup;
	}

	for (int i = 0; i < nonzeros1; i++) {
		if (fscanf(input_file1, "%d", &values1[i]) != 1) {
			printf("Failed to read values for first matrix\n");
			goto cleanup;
		}
	}

	for (int i = 0; i < nonzeros1; i++) {
		if (fscanf(input_file1, "%d", &column_indices1[i]) != 1) {
			printf("Failed to read column indices for first matrix\n");
			goto cleanup;
		}
	}

	for (int i = 0; i < rows1 + 1; i++) {
		if (fscanf(input_file1, "%d", &row_start1[i]) != 1) {
			printf("Failed to read row start for first matrix\n");
			goto cleanup;
		}
	}

	/* read second matrix */
	if (fscanf(input_file2, "%d", &rows2) != 1) {
		printf("Failed to read number of rows for second matrix\n");
		goto cleanup;
	}
	if (fscanf(input_file2, "%d", &nonzeros2) != 1) {
		printf("Failed to read number of non-zero elements for second matrix\n");
		goto cleanup;
	}

	if (rows1 != rows2) {
		printf("The number of rows in the matrices are not equal.\n");
		goto cleanup;
	}

	values2 = malloc(nonzeros2 * sizeof(int));
	column_indices2 = malloc(nonzeros2 * sizeof(int));
	row_start2 = malloc((rows2 + 1) * sizeof(int));

	if (values2 == NULL || column_indices2 == NULL || row_start2 == NULL) {
		printf("Memory allocation failed for second matrix\n");
		goto cleanup;
	}

	for (int i = 0; i < nonzeros2; i++) {
		if (fscanf(input_file2, "%d", &values2[i]) != 1) {
			printf("Failed to read values for second matrix\n");
			goto cleanup;
		}
	}

	for (int i = 0; i < nonzeros2; i++) {
		if (fscanf(input_file2, "%d", &column_indices2[i]) != 1) {
			printf("Failed to read column indices for second matrix\n");
			goto cleanup;
		}
	}

	for (int i = 0; i < rows2 + 1; i++) {
		if (fscanf(input_file2, "%d", &row_start2[i]) != 1) {
			printf("Failed to read row start for second matrix\n");
			goto cleanup;
		}
	}

	fclose(input_file1);
	input_file1 = NULL;
	fclose(input_file2);
	input_file2 = NULL;

	/* first pass: count nonzeros in result */
	num_rows = rows1;
	result_nonzeros = 0;

	for (int row = 0; row < num_rows; row++) {
		int row1_start_index = row_start1[row];
		int row1_end_index = row_start1[row + 1];
		int row2_start_index = row_start2[row];
		int row2_end_index = row_start2[row + 1];

		int index1 = row1_start_index;
		int index2 = row2_start_index;

		while (index1 < row1_end_index && index2 < row2_end_index) {
			int column1 = column_indices1[index1];
			int column2 = column_indices2[index2];

			if (column1 == column2) {
				int sum = values1[index1] + values2[index2];
				if (sum != 0) {
					result_nonzeros++;
				}
				index1++;
				index2++;
			} else if (column1 < column2) {
				result_nonzeros++;
				index1++;
			} else {
				result_nonzeros++;
				index2++;
			}
		}

		while (index1 < row1_end_index) {
			result_nonzeros++;
			index1++;
		}

		while (index2 < row2_end_index) {
			result_nonzeros++;
			index2++;
		}
	}

	result_values = malloc(result_nonzeros * sizeof(int));
	result_column_indices = malloc(result_nonzeros * sizeof(int));
	result_row_start = malloc((num_rows + 1) * sizeof(int));

	if (result_values == NULL || result_column_indices == NULL || result_row_start == NULL) {
		printf("Memory allocation failed for result matrix\n");
		goto cleanup;
	}

	/* second pass: fill result arrays */
	int result_index = 0;
	result_row_start[0] = 0;

	for (int row = 0; row < num_rows; row++) {
		int row1_start_index = row_start1[row];
		int row1_end_index = row_start1[row + 1];
		int row2_start_index = row_start2[row];
		int row2_end_index = row_start2[row + 1];

		int index1 = row1_start_index;
		int index2 = row2_start_index;

		while (index1 < row1_end_index && index2 < row2_end_index) {
			int column1 = column_indices1[index1];
			int column2 = column_indices2[index2];

			if (column1 == column2) {
				int sum = values1[index1] + values2[index2];
				if (sum != 0) {
					result_values[result_index] = sum;
					result_column_indices[result_index] = column1;
					result_index++;
				}
				index1++;
				index2++;
			} else if (column1 < column2) {
				result_values[result_index] = values1[index1];
				result_column_indices[result_index] = column1;
				result_index++;
				index1++;
			} else {
				result_values[result_index] = values2[index2];
				result_column_indices[result_index] = column2;
				result_index++;
				index2++;
			}
		}

		while (index1 < row1_end_index) {
			result_values[result_index] = values1[index1];
			result_column_indices[result_index] = column_indices1[index1];
			result_index++;
			index1++;
		}

		while (index2 < row2_end_index) {
			result_values[result_index] = values2[index2];
			result_column_indices[result_index] = column_indices2[index2];
			result_index++;
			index2++;
		}

		result_row_start[row + 1] = result_index;
	}

	output_file = fopen("sparse_result.txt", "w");
	if (output_file == NULL) {
		printf("Failed to open sparse_result.txt for writing\n");
		goto cleanup;
	}

	fprintf(output_file, "%d\n", num_rows);
	fprintf(output_file, "%d\n", result_nonzeros);

	for (int i = 0; i < result_nonzeros; i++) {
		fprintf(output_file, "%d\n", result_values[i]);
	}

	for (int i = 0; i < result_nonzeros; i++) {
		fprintf(output_file, "%d\n", result_column_indices[i]);
	}

	for (int i = 0; i < num_rows + 1; i++) {
		fprintf(output_file, "%d\n", result_row_start[i]);
	}

	fclose(output_file);
	output_file = NULL;

	exit_code = 0;

cleanup:
	if (input_file1 != NULL) {
		fclose(input_file1);
	}
	if (input_file2 != NULL) {
		fclose(input_file2);
	}
	if (output_file != NULL) {
		fclose(output_file);
	}

	free(values1);
	free(column_indices1);
	free(row_start1);
	free(values2);
	free(column_indices2);
	free(row_start2);
	free(result_values);
	free(result_column_indices);
	free(result_row_start);

	return exit_code;
}

