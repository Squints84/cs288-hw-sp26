#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define COUNT_ARRAY 1000
#define TAG_N 1
#define TAG_CHUNK 2
#define TAG_COUNT 3

int main(int argc, char **argv)
{
    int rank, size, num_workers;
    char path[4096];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    num_workers = size - 1;
    if (num_workers <= 0) {
        if (rank == 0) {
            fprintf(stderr, "Need at least 2 MPI processes (1 master + 1 worker).\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        int *buf = NULL;
        int *sorted = NULL;
        int n;
        long file_bytes;
        int chunk_size;
        FILE *fp;

        if (scanf("%4095s", path) != 1) {
            fprintf(stderr, "Failed to read file pathname.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        fp = fopen(path, "rb");
        if (!fp) {
            perror("fopen");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        if (fseek(fp, 0, SEEK_END) != 0) {
            perror("fseek");
            fclose(fp);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        file_bytes = ftell(fp);
        if (file_bytes < 0 || (file_bytes % (int)sizeof(int)) != 0) {
            fprintf(stderr, "Invalid file size.\n");
            fclose(fp);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        n = (int)(file_bytes / (int)sizeof(int));
        if (fseek(fp, 0, SEEK_SET) != 0) {
            perror("fseek");
            fclose(fp);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        buf = (int *)malloc((size_t)n * sizeof(int));
        if (!buf) {
            fprintf(stderr, "malloc failed.\n");
            fclose(fp);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        if (fread(buf, sizeof(int), (size_t)n, fp) != (size_t)n) {
            fprintf(stderr, "fread failed.\n");
            free(buf);
            fclose(fp);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        fclose(fp);

        chunk_size = n / num_workers;

        for (int dest = 1; dest <= num_workers; dest++) {
            MPI_Send(&n, 1, MPI_INT, dest, TAG_N, MPI_COMM_WORLD);
            MPI_Send(buf + (dest - 1) * chunk_size, chunk_size, MPI_INT, dest,
                     TAG_CHUNK, MPI_COMM_WORLD);
        }

        {
            int global[COUNT_ARRAY];
            for (int v = 0; v < COUNT_ARRAY; v++) {
                global[v] = 0;
            }

            for (int source = 1; source <= num_workers; source++) {
                int local[COUNT_ARRAY];
                MPI_Recv(local, COUNT_ARRAY, MPI_INT, source, TAG_COUNT,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int v = 0; v < COUNT_ARRAY; v++) {
                    global[v] += local[v];
                }
            }

            sorted = (int *)malloc((size_t)n * sizeof(int));
            if (!sorted) {
                fprintf(stderr, "malloc failed.\n");
                free(buf);
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            {
                int pos = 0;
                for (int v = 0; v < COUNT_ARRAY; v++) {
                    for (int k = 0; k < global[v]; k++) {
                        sorted[pos++] = v;
                    }
                }
            }

            fp = fopen(path, "wb");
            if (!fp) {
                perror("fopen");
                free(buf);
                free(sorted);
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            if (fwrite(sorted, sizeof(int), (size_t)n, fp) != (size_t)n) {
                fprintf(stderr, "fwrite failed.\n");
                fclose(fp);
                free(buf);
                free(sorted);
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            fclose(fp);
            free(buf);
            free(sorted);
        }
    } else {
        int n;
        int chunk_size;
        int *chunk;
        int local[COUNT_ARRAY];

        MPI_Recv(&n, 1, MPI_INT, 0, TAG_N, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        chunk_size = n / num_workers;

        chunk = (int *)malloc((size_t)chunk_size * sizeof(int));
        if (!chunk) {
            fprintf(stderr, "malloc failed (worker).\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        MPI_Recv(chunk, chunk_size, MPI_INT, 0, TAG_CHUNK, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        for (int v = 0; v < COUNT_ARRAY; v++) {
            local[v] = 0;
        }
        for (int i = 0; i < chunk_size; i++) {
            local[chunk[i]]++;
        }

        MPI_Send(local, COUNT_ARRAY, MPI_INT, 0, TAG_COUNT, MPI_COMM_WORLD);
        free(chunk);
    }

    MPI_Finalize();
    return 0;
}
