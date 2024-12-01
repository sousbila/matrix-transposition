# Matrix Transposition Performance Analysis

This repository contains the code and scripts used to analyze the performance of different matrix transposition implementations. The project focuses on optimizing matrix transposition operations using various techniques, including sequential methods, implicit parallelism with compiler optimizations, and explicit parallelism with OpenMP.

## Table of Contents

- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Instructions](#instructions)
  - [Compiling and Running the Main Code](#compiling-and-running-the-main-code)
    - [Using the PBS Script](#using-the-pbs-script)
    - [Manual Execution](#manual-execution)
  - [Testing Explicit Implementations](#testing-explicit-implementations)
  - [Testing Implicit Implementations with Different Compiler Flags](#testing-implicit-implementations-with-different-compiler-flags)
- [Output Files](#output-files)
- [Notes](#notes)

## Project Structure
```plaintext
matrix-transposition/
│
├── README.md
└── d1_project/
    ├── mainCode/                    # Main code for the project
    │   ├── build.sh                 # Script to build the code
    │   ├── run.sh                   # Script to run the experiments
    │   ├── implicitScript.sh        # Script to test implicit method with different flags
    │   ├── serial.c                 # Contains 'serial' method
    │   ├── serial.h
    │   ├── implicit.c               # Contains 'implicit' method
    │   ├── implicit.h
    │   ├── explicit.c               # Contains 'omp' method
    │   ├── explicit.h
    │   ├── explicitblock.c          # Contains 'omp2' method
    │   ├── explicitblock.h
    │   ├── main.c                   # Main function
    │   ├── utils.c                  # Utility functions
    │   └── utils.h
    ├── explicitTest/                # For testing explicit implementations
    │   ├── buildExp.sh              # Script to build and link files
    │   ├── runExp.sh                # Script to run the program
    │   ├── explicit.c               # Contains 'omp' method
    │   ├── explicit.h
    │   ├── explicit1.c              # Contains 'omp1' method
    │   ├── explicit1.h
    │   ├── explicit2.c              # Contains 'omp2' method
    │   ├── explicit2.h
    │   ├── explicit3.c              # Contains 'omp3' method
    │   └── explicit3.h
    │
    └── submit.pbs                   # PBS script to run the main experiments
```

## Requirements

- C Compiler: GCC 9.1.0 (or compatible version with OpenMP support)
- OpenMP: For parallel implementations
- Bash: For executing shell scripts

## Instructions

### Compiling and Running the Main Code

#### Using the PBS Script

To reproduce the main results and obtain the performance measurements for the best four methods (`serial`, `implicit` with blocking, `omp`, and `omp2`), follow these steps:

1. Navigate to the Project Directory:
   ```bash
   cd matrix-transposition/d1_project

2. Submit the PBS Job:
   ```
   qsub submit.pbs
   ```
   **Note:**
   - The `submit.pbs` script will:
     - Load the required GCC module.
     - Compile the code using `build.sh` located in `mainCode/`.
     - Run the experiments using `run.sh` located in `mainCode/`.
     - The output file `transpose_times.csv` will be created in the `d1_project/` directory.

3. Retrieve the Output:
   - `transpose_times.csv` in `d1_project/` contains measurements for the best four methods (`serial`, `implicit`, `explicit`, `explicitblock`) across different matrix sizes and thread counts.
   - Standard output and error logs (`matrix_transpose.out` and `matrix_transpose.err`).

#### Manual Execution

If you prefer to run the code interactively:

1. Open an Interactive Session:
   ```
   qsub -I -q short_cpu -l select=1:ncpus=96:ompthreads=96:mem=512mb
   ```

2. Navigate to the `mainCode/` Directory:
   ```
   cd matrix-transposition/d1_project/mainCode
   ```

3. Load the GCC Module:
   ```
   module load gcc91
   ```

4. Compile the Code:
   ```
   chmod +x build.sh
   ./build.sh
   ```

5. Run the Experiments Using one of the methods specified:

   a) Run one of the four methods (`serial`, `implicit`, `explicitblock` or `explicit`) with a specified exponent (from `4` to `12`)
   ```
   export OMP_NUM_THREADS='number of threads'; ./$OUTPUT 'exponent' 'method'
   ```
   b) Run all four methods with a specified exponent (from `4` to `12`)
   ```
   export OMP_NUM_THREADS='number of threads'; ./$OUTPUT 'exponent'
   ```

   c) Run the same script that the .pbs is running
   ```
   chmod +x run.sh
   ./run.sh
   ```

   - The `transpose_times.csv` file will be created in the parent directory `d1_project/`.

### Testing Explicit Implementations

To analyze and compare different explicit methods (`omp`, `omp1`, `omp2`, `omp3`), you can use the scripts in the `explicitTest/` directory.

1. Navigate to the `explicitTest/` Directory:
   ```
   cd matrix-transposition/d1_project/explicitTest
   ```

2. Load the GCC Module:
   ```
   module load gcc91
   ```

3. Compile the Explicit Methods:
   - Make sure the `buildExp.sh` script is executable:
     ```
     chmod +x buildExp.sh
     ./buildExp.sh
     ```

4. Run the Experiments:
   - Make sure the `runExp.sh` script is executable:
     ```
     chmod +x runExp.sh
     ./runExp.sh
     ```

5. Output:
   - The measurements will be saved in `explicit_times.csv` located in the `d1_project/` directory.
   - Each command is executed 5 times to allow calculation of average times and plotting of graphs in Python.

## Testing Implicit Implementations with Different Compiler Flags

To test the implicit method with various compiler optimization flags, use the `implicitScript.sh` script in the `mainCode/` directory.

1. **Navigate to the `mainCode\` Directory:**
   ```bash
   cd matrix-transposition/d1_project/mainCode
   ```

2. **Load the GCC Module:**
   ```bash
   module load gcc91
   ```

3. **Make the Script Executable:**
   ```bash
   chmod +x implicitScript.sh
   ```

4. **Run the Script:**
   ```bash
   ./implicitScript.sh
   ```

   This script compiles the implicit method with different combinations of compiler flags and measures the execution time.

5. **Output:**
   - The measurements will be saved in `implicit_times.csv` located in the `d1_project/` directory.

## Output Files

- `transpose_times.csv`: Contains measurements for the best four methods (`serial`, `implicit`, `explicit`, `explicitblock`) across different matrix sizes and thread counts. Generated by `run.sh` in `mainCode/`.
- `explicit_times.csv`: Contains measurements for the explicit methods (`omp`, `omp1`, `omp2`, `omp3`) across different matrix sizes and thread counts. Generated by `runExp.sh` in `explicitTest/`.
- `implicit_times.csv`: Contains measurements for the implicit method compiled with different compiler flags across various matrix sizes. Generated by `implicitScript.sh` in `mainCode/`.

Note: All output files are created in the `d1_project/` directory (parent directory of `mainCode/` and `explicitTest/`).

## Notes

- **Measurement Repetition**: Each experiment is executed 5 times to account for variability in execution time. The average time can be calculated from these measurements for more accurate analysis.
- **Plotting Results**: The generated `.csv` files can be used to plot graphs and analyze the performance of different methods using tools like Python's `matplotlib` or `pandas`.
- **PBS Script**: The `submit.pbs` script is configured to compile and run the main experiments automatically on a cluster using the PBS job scheduler. Adjust the resource requests and module loads as needed for your specific environment.
- **Environment Setup**:
  - Ensure that the GCC 9.1.0 module (`gcc91`) is available on your system.
  - The scripts assume a Unix-like environment with Bash shell.
- **Permissions**:
  - Before running any scripts, make sure they have executable permissions (`chmod +x script.sh`).

