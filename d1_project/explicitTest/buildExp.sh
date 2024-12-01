#!/bin/bash

# Define the compiler 
CC=gcc  # After module load, gcc should be GCC 9.1.0

# Compiler flags for each module
CFLAGS_COMMON="-std=c99"
CFLAGS_EXPLICIT1="-fopenmp"
CFLAGS_EXPLICIT2="-fopenmp"
CFLAGS_EXPLICIT3="-fopenmp"

# Output executable name
OUTPUT="program"

# Clean old binary
echo "Cleaning old binaries..."
rm -f $OUTPUT *.o

# Compile each part with its specific flags
echo "Compiling explicit.c..."
$CC $CFLAGS_COMMON $CFLAGS_EXPLICIT -c explicit.c -o explicit.o

echo "Compiling explicit1.c..."
$CC $CFLAGS_COMMON $CFLAGS_EXPLICIT1 -c explicit1.c -o explicit1.o

echo "Compiling explicit2.c..."
$CC $CFLAGS_COMMON $CFLAGS_EXPLICIT2 -c explicit2.c -o explicit2.o

echo "Compiling explicit3.c..."
$CC $CFLAGS_COMMON $CFLAGS_EXPLICIT3 -c explicit3.c -o explicit3.o

echo "Compiling main.c and utils.c with common flags..."
$CC $CFLAGS_COMMON -c main.c -o main.o
$CC $CFLAGS_COMMON -c utils.c -o utils.o

# Link all object files into a single executable
echo "Linking all object files into the executable..."
$CC main.o utils.o explicit.o explicit1.o explicit2.o explicit3.o -o $OUTPUT -fopenmp -lm

echo "Build completed. Run the program with ./$OUTPUT 'exponent' 'method -> (omp or omp1 or omp2 or omp3)'"
