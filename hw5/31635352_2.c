#include <stdio.h>

#define MAX 100
#define RADIX 16

static void hex_radix_sort_signed_ints(int arr[], int n) {
    unsigned int keys[MAX];
    unsigned int buckets[RADIX][MAX];
    int bucket_count[RADIX];

    for (int i = 0; i < n; i++) {
        /* Convert signed values so unsigned sort gives signed order. */
        keys[i] = ((unsigned int)arr[i]) ^ 0x80000000u;
    }

    /* 8 hex digits in a 32-bit integer => 8 passes. */
    for (int pass = 0; pass < 8; pass++) {
        int shift = pass * 4;

        for (int b = 0; b < RADIX; b++) {
            bucket_count[b] = 0;
        }

        for (int i = 0; i < n; i++) {
            int bucket = (int)((keys[i] >> shift) & 0xFu);
            buckets[bucket][bucket_count[bucket]++] = keys[i];
        }

        int idx = 0;
        for (int b = 0; b < RADIX; b++) {
            for (int j = 0; j < bucket_count[b]; j++) {
                keys[idx++] = buckets[b][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        arr[i] = (int)(keys[i] ^ 0x80000000u);
    }
}

int main() {
    unsigned int elements, i = 0;
    int arr[MAX];

    if (scanf("%u", &elements) != 1 || elements > 100 || elements <= 0) {
        return 1;
    }

    while (i < elements) {
        if (scanf("%d", &arr[i]) != 1) {
            return 1;
        }
        i++;
    }

    hex_radix_sort_signed_ints(arr, (int)elements);
    for (unsigned int i = 0; i < elements; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}
