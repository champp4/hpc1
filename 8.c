#include <stdio.h>
#include <mpi.h>

#define SIZE 16
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int main(int argc, char* argv[]) {
    int rank, numtasks, nbrs[4], inbuf[4], outbuf, dims[2] = {4, 4}, periods[2] = {0, 0};
    MPI_Request reqs[8];
    MPI_Comm cartcomm;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks != SIZE) {
        if (rank == 0) printf("Must specify %d tasks. Terminating.\n", SIZE);
        MPI_Finalize();
        return 0;
    }

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cartcomm);
    MPI_Comm_rank(cartcomm, &rank);
    MPI_Cart_shift(cartcomm, 0, 1, &nbrs[UP], &nbrs[DOWN]);
    MPI_Cart_shift(cartcomm, 1, 1, &nbrs[LEFT], &nbrs[RIGHT]);

    outbuf = rank;
    for (int i = 0; i < 4; i++) {
        MPI_Isend(&outbuf, 1, MPI_INT, nbrs[i], 1, MPI_COMM_WORLD, &reqs[i]);
        MPI_Irecv(&inbuf[i], 1, MPI_INT, nbrs[i], 1, MPI_COMM_WORLD, &reqs[i + 4]);
    }

    MPI_Waitall(8, reqs, MPI_STATUSES_IGNORE);
    printf("rank= %d neighbors(u,d,l,r)= %d %d %d %d inbuf= %d %d %d %d\n",
           rank, nbrs[UP], nbrs[DOWN], nbrs[LEFT], nbrs[RIGHT],
           inbuf[UP], inbuf[DOWN], inbuf[LEFT], inbuf[RIGHT]);

    MPI_Finalize();
    return 0;
}
