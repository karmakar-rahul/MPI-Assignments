//4. Write a MPI program to calculate the total number of prime between 1 to 100 numbers  between 1 and 1,00,00,000.

#include <mpi.h>
#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    
    int limit = (int)sqrt(n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int N = 10000000;
    int local_count = 0;
    
    double start_time = MPI_Wtime();
    
    for (int i = 2 + world_rank; i <= N; i += world_size) {
        if (is_prime(i)) {
            local_count++;
        }
    }
    
    printf("Process %d found %d primes\n", world_rank, local_count);
    
    int total_count;
    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    double end_time = MPI_Wtime();
    
    if (world_rank == 0) {
        printf("\nTotal prime numbers between 1 and %d: %d\n", N, total_count);
        printf("Time taken: %.4f seconds\n", end_time - start_time);
    }
    
    MPI_Finalize();
    return 0;
}
