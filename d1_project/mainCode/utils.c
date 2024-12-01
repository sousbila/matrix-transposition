// utils.c
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

float** createMatrix(int n) {
    float** matrix = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (float*)malloc(n * sizeof(float));
        if (!matrix[i]) {
            fprintf(stderr, "Error allocating memory for matrix row %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

void freeMatrix(float** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void initializeMatrix(float** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (float)rand() / (float)RAND_MAX;
        }
    }
}

void printMatrix(float** matrix, int n) {
    printf("\nMatrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.3f\t", matrix[i][j]);
        }
        printf("\n\n");
    }
}

void printTransp(float** matrix, int n) {
    printf("\nTransposed:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.3f\t", matrix[i][j]);
        }
        printf("\n\n");
    }
}

void resetMatrix(float** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0.000;
        }
    }
}

float calculateChecksum(float** matrix, int n, int index, char type) {
    float checksum = 0;
    if (type == 'r') {  //Row checksum
        for (int j = 0; j < n; j++) {
            checksum += matrix[index][j];
        }
    } else if (type == 'c') {  //Column checksum
        for (int i = 0; i < n; i++) {
            checksum += matrix[i][index];
        }
    }
    return checksum;
}

int compareChecksums(float** mat1, float** mat2, int n, int checks) {
    for (int i = 0; i < checks; i++) {
        int index = rand() % n;
        if (calculateChecksum(mat1, n, index, 'r') != calculateChecksum(mat2, n, index, 'r') ||
            calculateChecksum(mat1, n, index, 'c') != calculateChecksum(mat2, n, index, 'c')) {
            return 0;
        }
    }
    return 1;
}

