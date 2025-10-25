#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    char message[50] = "Awaiting 2025";
    
    if (world_rank == 0) {
        printf("Rank 0: Sending message '%s' to all processes\n", message);
        for (int i = 1; i < world_size; i++) {
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        char recv_message[50];
        MPI_Recv(recv_message, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %d received: %s\n", world_rank, recv_message);
    }
    
    MPI_Finalize();
    return 0;
}
