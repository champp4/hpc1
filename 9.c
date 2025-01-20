#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, prev, next, inmsg;
    MPI_Status status;
    MPI_Request reqs[2];
    double blocking_start, blocking_end, nonblocking_start, nonblocking_end;

 
   MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

 
    prev = (rank == 0) ? size - 1 : rank - 1;  
    next = (rank == size - 1) ? 0 : rank + 1;  

  
    blocking_start = MPI_Wtime();
    if (rank % 2 == 0) {
        MPI_Send(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
    } else {
        MPI_Recv(&inmsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
        MPI_Send(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }
    blocking_end = MPI_Wtime();

 
    printf("Rank %d received message %d from rank %d (Blocking)\n", rank, inmsg, prev);
    if (rank == 0) {
        printf("Time taken by Blocking Send/Receive: %f seconds\n", blocking_end - blocking_start);
    }

    MPI_Barrier(MPI_COMM_WORLD);

   
    nonblocking_start = MPI_Wtime();
    MPI_Irecv(&inmsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &reqs[0]);
    MPI_Isend(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &reqs[1]);
    MPI_Waitall(2, reqs, MPI_STATUSES_IGNORE);
    nonblocking_end = MPI_Wtime();

    printf("Rank %d received message %d from rank %d (Non-Blocking)\n", rank, inmsg, prev);
    if (rank == 0) {
        printf("Time taken by Non-Blocking Send/Receive: %f seconds\n", nonblocking_end - nonblocking_start);
    }

    MPI_Finalize();
    return 0;
}

