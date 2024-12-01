#!/bin/bash

# Define the compiler and common compiler flags
CC=gcc-9.1.0
CFLAGS_COMMON="-std=c99 -fopenmp -lm"

# Output CSV file
output_file="../implicitVersus.csv"
echo "method,flags,number_of_threads,n,time_measured" > $output_file

# Compile all necessary source files
    $CC $CFLAGS_COMMON -c main.c -o main.o
    $CC $CFLAGS_COMMON -c utils.c -o utils.o
    $CC $CFLAGS_COMMON -c serial.c -o serial.o
    $CC $CFLAGS_COMMON -c explicit.c -o explicit.o
    $CC $CFLAGS_COMMON -c explicitblock.c -o explicitblock.o
    

# Function to compile, run and log results
compile_run_log() {
    local flags=$1
    local flags_description=$2
    
    echo "Compiling all sources with flags: $flags"
    $CC $CFLAGS_COMMON $flags -c implicit.c -o implicit.o
    
    # Link all object files into a single executable
    $CC main.o utils.o serial.o explicit.o explicitblock.o implicit.o -o program -fopenmp -lm

    # Execute the compiled program 5 times and log results
    for n in {4..12}; do
        #for run in {1..5}; do
            export OMP_NUM_THREADS=1  
            ./program $n implicit > temp_output.txt
            time_measured=$(tail -1 temp_output.txt)
            echo "implicit,$flags_description,1,$n,$time_measured" >> $output_file
        #done
    done
    rm temp_output.txt  # Clean up
}

# Compile and run with different flag combinations
compile_run_log "" "noflags"
compile_run_log "-O1" "O1"
compile_run_log "-O1 -march=native" "O1 -march_native"
compile_run_log "-O2" "O2"
compile_run_log "-O2 -funroll-loops" "O2 -funroll-loops"
compile_run_log "-O2 -fprefetch-loop-arrays" "O2 -fprefetch-loop-array"
compile_run_log "-O2 -ftree-vectorize" "O2  -ftree-vectorize"
compile_run_log "-O2 -march=native" "O2 -march=native"
compile_run_log "-O2 -funroll-loops -march=native" "O2 -funroll-loops -march=native"
compile_run_log "-O2 -ftree-vectorize -march=native" "O2 -ftree-vectorize -march=native"
#compile_run_log "-O2 -march=native -ftree-vectorize -funroll-loops" "O2 senza -ftree-vectorize"
compile_run_log "-O2 -funroll-loops -fprefetch-loop-arrays -ftree-vectorize -march=native" "O2_all"
#compile_run_log "-O2 -funroll-loops -fprefetch-loop-arrays -ftree-vectorize" "O2_all senza march"

echo "Build and test completed. Results saved to $output_file."