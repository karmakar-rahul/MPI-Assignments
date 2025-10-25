# MPI Assignments

## Objective
The purpose of this repository is to explore and implement key concepts of parallel computing using the Message Passing Interface (MPI). Each assignment demonstrates how distributed processes can communicate, synchronize, and share workloads efficiently.

## Implementation
The assignments are implemented in C using the MPI library. Each program focuses on specific aspects such as:
- Process rank identification
- Data broadcasting and scattering
- Collective communication
- Point-to-point message passing
- Performance benchmarking for scalability analysis

Compilation is done using `mpicc`, and execution uses `mpirun`.

## Usage
To compile and run:
```bash
mpicc <filename>.c -o <output_name>
mpirun -np <number_of_processes> ./<output_name>
##Example
mpicc matrix_multiply.c -o matrix_multiply
mpirun -np 4 ./matrix_multiply

```

## Results and Observations

Each experiment highlights the advantages of distributed computing and demonstrates how communication overhead affects performance as the number of processes increases. Observations can be further analyzed using timing data and scalability graphs.

## Directory Structure
MPI_Assignments/
├── <source_files>.c
├── README.md
└── git_log.txt

**Technology:** OpenMPI 4.1.6  
**Language:** C  
**Platform:** Ubuntu/WSL

## Acknowledgements
C-DAC Bangalore and C-DAC CINE instructors and OpenMPI Community.

## Author
Rahul Karmakar
### ⭐ If you found this helpful, please star this repository!

