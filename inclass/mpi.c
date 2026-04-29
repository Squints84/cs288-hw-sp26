#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv){
   // start the MPI environment
   MPI_Init(&argc, &argv);

   // get the rank/ID for each process
   // each process is idenitified by its rank
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   // MPI_COMM_WORLD => refers to the group of processees attached to program

   // get the size/total number of processes
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   // end of MPI environment
   MPI_Finalize();
}
