//1. To write a MPI program to print hostname an send message from process with rank 0 to all other.

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    char hostname[256];
    gethostname(hostname, 256);
    
    printf("Process rank %d running on hostname: %s\n", world_rank, hostname);
    
    if (world_rank == 0) {
        char message[100] = "Hello from rank 0!";
        for (int i = 1; i < world_size; i++) {
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            printf("Rank 0 sent message to rank %d\n", i);
        }
    } else {
        char recv_message[100];
        MPI_Recv(recv_message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %d received message: %s\n", world_rank, recv_message);
    }
    
    MPI_Finalize();
    return 0;
}
