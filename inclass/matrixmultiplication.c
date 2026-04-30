#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define N 100
#define FROM_ROOT 1
#define FROM_WORKER 2

int main(int argc, char **argv[])
{
    int rank, size, num_workers, rows;
    double a[N][N], b[N][N], c[N][N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    num_workers = size - 1;
    rows = N / num_workers;

    // size is the total number of processes
    if (rank == 0) 
    {
        // prepare the data -> initalize the data
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = i + j;
                b[i][j] = i * j;
            }
        }
    
    // send the data to worker processes (point to point communication function)
    // MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
    // MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);

    for (int dest = 1; dest <= num_workers; dest++) {
        // sending rows in chunks for matrix a
        MPI_Send(&a[(dest - 1) * rows][0], rows * N, MPI_DOUBLE, dest, FROM_ROOT, MPI_COMM_WORLD);
        // send the entire matrix b
        MPI_Send(&b, N*N, MPI_DOUBLE, dest, FROM_ROOT, MPI_COMM_WORLD);
    
    }
    // receive results from worker processes
    for (int source = 1; source <= num_workers; source++) {
        MPI_Recv(&c, rows*N, MPI_DOUBLE, source, FROM_WORKER, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    // print the result
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%f ", c[i][j]);
            }
            printf("\n");
        }
    }


    if (rank > 0) 
    {
        // receive the data from the root process
        MPI_Recv(&a, rows*N, MPI_DOUBLE, 0, FROM_ROOT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&b, N*N, MPI_DOUBLE, 0, FROM_ROOT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // perform the matrix multiplication
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }

        // send the result from worker processes to root process
        MPI_Send(&c, rows*N, MPI_DOUBLE, 0, FROM_WORKER, MPI_COMM_WORLD);
    }
}

        
