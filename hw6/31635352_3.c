#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
  int count = 0;

  (void)argc;
  (void)argv;

  while (envp[count] != NULL) {
    count++;
  }

  /* Bubble sort pointers in envp by variable name. */
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - 1 - i; j++) {
      char *left = envp[j];
      char *right = envp[j + 1];

      char *left_name = strtok(left, "=");
      char *right_name = strtok(right, "=");

      int cmp = strcmp(left_name, right_name);

      /* Put '=' back after name for both entries. */
      left[strlen(left_name)] = '=';
      right[strlen(right_name)] = '=';

      if (cmp > 0) {
        char *tmp = envp[j];
        envp[j] = envp[j + 1];
        envp[j + 1] = tmp;
      }
    }
  }

  for (int i = 0; i < count; i++) {
    printf("%s\n", envp[i]);
  }

  return 0;
}
