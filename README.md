MPI Histogram Project

A simple parallel computing project that demonstrates counting the frequency of digits (0-9) in a large dataset using MPI (Message Passing Interface) in C++. This project showcases basic concepts of parallel programming, including data distribution, local computation, and result gathering.

🚀 Features

Parallel computing with MPI

Data distribution with MPI_Scatter

Result aggregation with MPI_Gather

Calculates the frequency of digits in a randomly generated dataset

Measures execution time for distributed computation

🛠️ Technologies Used

C++: Core programming language

MPI (OpenMPI): Parallel processing library

Terminal / Command line: Compilation and execution

Linux / Mac / Windows: Cross-platform support

📋 Project Structure
mpi_histogram/
├── mpi_histogram.cpp   # Main C++ MPI program
└── README.md           # Project documentation

⚡ How It Works

The root process generates an array of random digits (0-9).

The array is divided among all available processes using MPI_Scatter.

Each process counts the frequency of each digit in its local data.

The local results are gathered back to the root process using MPI_Gather.

The root process sums the results and prints the global histogram.

Execution time is measured with MPI_Wtime.

💻 Getting Started
Prerequisites

C++ compiler with MPI support (e.g., mpic++)

OpenMPI installed

Compilation
mpic++ mpi_histogram.cpp -o mpi_histogram

Execution
mpiexec -n 4 ./mpi_histogram


-n 4 specifies the number of processes (you can change this).

📊 Example Output
Process:0/4
Process:1/4
Process:2/4
Process:3/4
Histogram:
0 : 1002
1 : 980
2 : 1015
3 : 995
4 : 1007
5 : 1010
6 : 980
7 : 1011
8 : 1000
9 : 1010
4 Process total time: 0.0023 s

📚 Key Learning Points

Understanding parallel programming concepts

Working with MPI communication functions (Scatter, Gather)

Counting data frequency in parallel

Measuring execution time in distributed systems


🔗 Notes

This project is educational and demonstrates the basic MPI workflow.

It can be extended to larger datasets, more categories, or different data analysis tasks
