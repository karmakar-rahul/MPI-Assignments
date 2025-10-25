//3. To write MPI program to find minimum of 40 numbers using 4 processes

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int total_numbers = 40;
    int numbers_per_process = total_numbers / world_size;
    int* all_numbers = NULL;
    int* sub_numbers = (int*)malloc(numbers_per_process * sizeof(int));
    
    if (world_rank == 0) {
        all_numbers = (int*)malloc(total_numbers * sizeof(int));
        printf("Original 40 numbers:\n");
        for (int i = 0; i < total_numbers; i++) {
            all_numbers[i] = rand() % 1000;
            printf("%d ", all_numbers[i]);
            if ((i + 1) % 10 == 0) printf("\n");
        }
        printf("\n");
    }
    
    MPI_Scatter(all_numbers, numbers_per_process, MPI_INT, 
                sub_numbers, numbers_per_process, MPI_INT, 
                0, MPI_COMM_WORLD);
    
    int local_min = INT_MAX;
    for (int i = 0; i < numbers_per_process; i++) {
        if (sub_numbers[i] < local_min) {
            local_min = sub_numbers[i];
        }
    }
    
    printf("Process %d: Local minimum = %d\n", world_rank, local_min);
    
    int global_min;
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    
    if (world_rank == 0) {
        printf("\nGlobal minimum of 40 numbers = %d\n", global_min);
        free(all_numbers);
    }
    
    free(sub_numbers);
    MPI_Finalize();
    return 0;
}
