#!/bin/bash

# Output file
output_file="../explicitVersus.csv"
echo "method,number_of_threads,n,time_measured" > $output_file

# Function to run the program and save the output
run_program_and_log() {
    local method=$1
    local threads=$2
    local exponent=$3

    export OMP_NUM_THREADS=$threads  # Set the number of threads for this run
    for run in {1..5}; do
        ./program $exponent $method > temp_output.txt
        time_measured=$(tail -1 temp_output.txt)
        echo "$method,$threads,$exponent,$time_measured" >> $output_file
    done
}

# Define the array of methods
methods=(omp omp1 omp2 omp3)

# Loop over the set of thread counts
for threads in 4 8 16 32 64 96; do
    # Loop over the exponent values from 4 to 12
    for exponent in {4..12}; do
        # Loop over each method
        for method in "${methods[@]}"; do
            run_program_and_log $method $threads $exponent
        done
    done
done

# Cleanup the temporary output file
rm temp_output.txt
echo "Tests completed. Results saved to $output_file."
