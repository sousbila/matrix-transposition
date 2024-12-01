#!/bin/bash

# Output file
output_file="../transpose_times.csv"
echo "method,number_of_threads,n,time_measured" > $output_file

# Function to run the program and save the output
run_program_and_log() {
    local method=$1
    local threads=$2
    for i in {4..12}; do
        export OMP_NUM_THREADS=$threads  # Set the number of threads for each run
        ./program $i $method > temp_output.txt
        time_measured=$(tail -1 temp_output.txt)
        echo "$method,$threads,$i,$time_measured" >> $output_file
        rm temp_output.txt  # Optionally delete temp_output.txt if it's no longer needed
    done
}

# Run the program for 'serial' and 'implicit' methods ensuring single-thread
for method in serial implicit; do
    for i in {4..12}; do
        export OMP_NUM_THREADS=1  # Ensure single-thread for these methods
        ./program $i $method > temp_output.txt
        time_measured=$(tail -1 temp_output.txt)
        echo "$method,1,$i,$time_measured" >> $output_file
        rm temp_output.txt
    done
done

# Run the program with the 'explicit' method for different OMP_NUM_THREADS
for threads in 2 4 8 16 32 64 96; do
    run_program_and_log explicit $threads
done

for threads in 2 4 8 16 32 64 96; do
    run_program_and_log explicitblock $threads
done