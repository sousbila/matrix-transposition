#ifndef UTILS_H
#define UTILS_H

float** createMatrix(int n);
void freeMatrix(float** matrix, int n);
void initializeMatrix(float** matrix, int n);
void printMatrix(float** matrix, int n);
void printTransp(float** matrix, int n);
void resetMatrix(float** matrix, int n);
float calculateChecksum(float** matrix, int n, int index, char type);
int compareChecksums(float** mat1, float** mat2, int n, int checks);


#endif