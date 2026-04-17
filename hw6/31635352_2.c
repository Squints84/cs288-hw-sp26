#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int opt;

  while ((opt = getopt(argc, argv, ":cduf:s:")) != -1) {
    switch (opt) {
    case 'c':
      printf("option: -c (count)\n");
      break;
    case 'd':
      printf("option: -d (duplicates only)\n");
      break;
    case 'u':
      printf("option: -u (unique only)\n");
      break;
    case 'f':
      printf("option: -f, argument (fields): %s\n", optarg);
      break;
    case 's':
      printf("option: -s, argument (char): %s\n", optarg);
      break;
    case ':':
      fprintf(stderr, "error: option -%c requires an argument\n", optopt);
      break;
    case '?':
      fprintf(stderr, "error: invalid option -%c\n", optopt);
      break;
    default:
      fprintf(stderr, "error: getopt returned unexpected value '%c'\n", opt);
      break;
    }

    printf("  optopt = '%c', ", optopt ? optopt : '0');
    if (optarg != NULL) {
      printf("optarg = \"%s\", ", optarg);
    } else {
      printf("optarg = NULL, ");
    }
    printf("optind = %d\n", optind);
  }

  printf("\noperands (starting at argv[optind]):\n");
  for (int i = optind; i < argc; i++) {
    printf("  argv[%d] = %s\n", i, argv[i]);
  }

  if (optind >= argc) {
    printf("  (none)\n");
  }
  return 0;
}
