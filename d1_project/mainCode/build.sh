#!/bin/bash

# Define the compiler 
CC=gcc  # After module load, gcc should be GCC 9.1.0

# Compiler flags for each module
CFLAGS_COMMON="-std=c99"
CFLAGS_IMPLICIT="-O2 -funroll-loops -march=native"
CFLAGS_EXPLICIT="-fopenmp" 

# Output executable name
OUTPUT="program"

# Clean old binary
echo "Cleaning old binaries..."
rm -f $OUTPUT *.o

# Compile each part with its specific flags
echo "Compiling serial.c..."
$CC $CFLAGS_COMMON -c serial.c -o serial.o
echo "Compiling implicit.c..."
$CC $CFLAGS_COMMON $CFLAGS_IMPLICIT -c implicit.c -o implicit.o
# $CC $CFLAGS_IMPLICIT -c implicit.c -o implicit.o

echo "Compiling explicit.c..."
$CC $CFLAGS_COMMON $CFLAGS_EXPLICIT -c explicit.c -o explicit.o

echo "Compiling explicitblock.c..."
$CC $CFLAGS_COMMON $CFLAGS_EXPLICIT -c explicitblock.c -o explicitblock.o

echo "Compiling main.c and utils.c with common flags..."
$CC $CFLAGS_COMMON -c main.c -o main.o
$CC $CFLAGS_COMMON -c utils.c -o utils.o

# Link all object files into a single executable
echo "Linking all object files into the executable..."
$CC main.o utils.o serial.o implicit.o explicit.o explicitblock.o -o $OUTPUT -fopenmp -lm

echo "Build completed." 
#Run the program with (1) ./$OUTPUT 'exponent' 'method' or (2) ./$OUTPUT 'exponent' or (3) ./run.sh"
