#include <stdio.h>
#include <mpi.h>

#define SIZE 16

int main(int argc, char* argv[]) {
    int rank, numtasks, nbrs[4], outbuf, inbuf[4];
    MPI_Request reqs[8];
    MPI_Comm cartcomm;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks == SIZE) {  // Ensure we have 16 processes
        MPI_Cart_create(MPI_COMM_WORLD, 2, (int[]){4, 4}, (int[]){0, 0}, 0, &cartcomm);
        MPI_Comm_rank(cartcomm, &rank);
        MPI_Cart_shift(cartcomm, 0, 1, &nbrs[0], &nbrs[1]); // UP, DOWN
        MPI_Cart_shift(cartcomm, 1, 1, &nbrs[2], &nbrs[3]); // LEFT, RIGHT

        outbuf = rank;
        for (int i = 0; i < 4; i++) {
            MPI_Isend(&outbuf, 1, MPI_INT, nbrs[i], 1, cartcomm, &reqs[i]);
            MPI_Irecv(&inbuf[i], 1, MPI_INT, nbrs[i], 1, cartcomm, &reqs[i + 4]);
        }

        MPI_Waitall(8, reqs, MPI_STATUS_IGNORE);
        printf("rank= %d received= %d %d %d %d\n", rank, inbuf[0], inbuf[1], inbuf[2], inbuf[3]);
    } else {
        printf("Must specify %d tasks. Terminating.\n", SIZE);
    }

    MPI_Finalize();
    return 0;
}

