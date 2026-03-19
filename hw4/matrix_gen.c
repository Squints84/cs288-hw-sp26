#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void write_matrices_to_binary(int n) {
  FILE *f_rand = fopen("random_matrix.bin", "wb");
  FILE *f_ident = fopen("identity_matrix.bin", "wb");

  if (f_rand == NULL || f_ident == NULL) {
    perror("Error opening files");
    exit(1);
  }

  // Write the dimension 'n' as the first element in both files
  fwrite(&n, sizeof(int), 1, f_rand);
  fwrite(&n, sizeof(int), 1, f_ident);

  srand(time(NULL));

  // Generate and write the matrices
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // Logic for Random Matrix
      int rand_val = rand() % 100;
      fwrite(&rand_val, sizeof(int), 1, f_rand);

      // Logic for Identity Matrix
      int ident_val = (i == j) ? 1 : 0;
      fwrite(&ident_val, sizeof(int), 1, f_ident);
    }
  }

  fclose(f_rand);
  fclose(f_ident);
  printf("Successfully wrote to random_matrix.bin and identity_matrix.bin\n");
}

int main() {
  int n;

  printf("Enter dimension n: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    fprintf(stderr, "Invalid input.\n");
    return 1;
  }

  write_matrices_to_binary(n);

  return 0;
}
