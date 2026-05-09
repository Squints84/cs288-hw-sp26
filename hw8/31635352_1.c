#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

double *A, *B;
double global_sum = 0.0;
long nthreads, length;
pthread_mutex_t sum_mutex;

void *dot_worker(void *id) {
    long myid = *(long *)id;
    long chunk = length / nthreads;
    long start = myid * chunk;
    long end = start + chunk;

    if (myid == nthreads - 1) {
        end = length;
    }

    double local_sum = 0.0;
    for (long i = start; i < end; i++) {
        local_sum += A[i] * B[i];
    }

    pthread_mutex_lock(&sum_mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&sum_mutex);

    return NULL;
}

double dot_serial(void) {
    double sum = 0.0;
    for (long i = 0; i < length; i++) {
        sum += A[i] * B[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_threads> <N>\n", argv[0]);
        return 1;
    }

    nthreads = strtol(argv[1], NULL, 10);
    length = strtol(argv[2], NULL, 10);
    if (nthreads <= 0 || length <= 0) {
        fprintf(stderr, "Error: <num_threads> and <N> must be positive.\n");
        return 1;
    }

    pthread_t *thread_array = malloc((size_t)nthreads * sizeof(pthread_t));
    long *thread_ids = malloc((size_t)nthreads * sizeof(long));
    A = malloc((size_t)length * sizeof(double));
    B = malloc((size_t)length * sizeof(double));
    if (thread_array == NULL || thread_ids == NULL || A == NULL || B == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(thread_array);
        free(thread_ids);
        free(A);
        free(B);
        return 1;
    }

    srand48(1);
    for (long i = 0; i < length; i++) {
        A[i] = drand48();
        B[i] = drand48();
    }

    pthread_mutex_init(&sum_mutex, NULL);

    for (long i = 0; i < nthreads; i++) {
        thread_ids[i] = i;
        pthread_create(&thread_array[i], NULL, dot_worker, &thread_ids[i]);
    }

    for (long i = 0; i < nthreads; i++) {
        pthread_join(thread_array[i], NULL);
    }

    double serial_sum = dot_serial();
    double diff = fabs(global_sum - serial_sum);

    printf("Parallel dot product: %.12f\n", global_sum);
    printf("Serial dot product:   %.12f\n", serial_sum);
    printf("Absolute difference:  %.12e\n", diff);

    pthread_mutex_destroy(&sum_mutex);
    free(thread_array);
    free(thread_ids);
    free(A);
    free(B);
    return 0;
}
