# MPI Histogram 📊

A parallel C++ program using **MPI** to calculate the frequency of digits (0-9) in a large dataset. Demonstrates data distribution, local computation, and result aggregation in a multi-process environment. 🚀

## Features ✨

- **Parallel computation** with MPI  
- **Data distribution** using `MPI_Scatter`  
- **Result collection** using `MPI_Gather`  
- **Execution time measurement** ⏱️  
- Works on **Mac, Linux, and Windows** 💻  

## How It Works ⚙️

1. The **root process** generates an array of random digits (0-9).  
2. The array is divided among all processes using **`MPI_Scatter`**.  
3. Each process counts the frequency of digits in its assigned portion.  
4. Results are gathered to the root process using **`MPI_Gather`**.  
5. The root process sums the local counts and prints the **global histogram**.  
6. Execution time is measured using **`MPI_Wtime`**.  

## Usage 🛠️

### Requirements

- C++ compiler with MPI support (e.g., `mpic++`)  
- OpenMPI installed  

### Compile

```bash
mpic++ mpi_histogram.cpp -o mpi_histogram

