#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

/* helper function to print the bytes of a variable */
static void print_bytes_8(const unsigned char *p) {
  for (int i = 7; i >= 0; i--) {
    printf("%02hhx%s", p[i], (i == 0 ? "" : " "));
  }
}

/* helper function to print the character view of a byte */
static void print_char_view(unsigned char b) {
  if (isprint(b)) {
    printf("  %c ", b);
    return;
  }
  if (b == '\0') {
    printf(" \\0 ");
    return;
  }
  printf("\\%03u", (unsigned)b);
}

int main(int argc, char **argv) {
  unsigned char *p = (unsigned char *)&argv;
  printf("%-10s", "argv");
  print_bytes_8(p);
  printf(" | %p\n", (void *)&argv);

  putchar('\n');

  for (int i = 0; i < argc; i++) {
    p = (unsigned char *)&argv[i];
    printf("argv[%d]   ", i);
    print_bytes_8(p);
    printf(" | %p\n", (void *)&argv[i]);
  }

  putchar('\n');

  /* Part 3: 8-byte-aligned dump that covers all argument strings. */
  if (argc > 0 && argv != NULL && argv[0] != NULL) {
    uintptr_t first = (uintptr_t)argv[0];
    uintptr_t last = (uintptr_t)argv[argc - 1];

    /* Move to the '\0' after the last argument. */
    unsigned char *end_ptr = (unsigned char *)last;
    while (*end_ptr != '\0') {
      end_ptr++;
    }
    end_ptr++;

    /* Align boundaries to 8 bytes. */
    uintptr_t start = first & ~(uintptr_t)0x7;
    uintptr_t end = ((uintptr_t)end_ptr + 7u) & ~(uintptr_t)0x7;

    for (uintptr_t addr = start; addr < end; addr += 8) {
      unsigned char *line = (unsigned char *)addr;

      print_bytes_8(line);
      printf(" |");
      for (int i = 7; i >= 0; i--) {
        putchar(' ');
        print_char_view(line[i]);
      }
      printf(" | %p\n", (void *)addr);
    }
  }

  return 0;
}

