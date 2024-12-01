#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <string.h>
#include "utils.h"
#include "serial.h"
#include "implicit.h"
#include "explicit.h"
#include "explicitblock.h"

void runAllTests(float** matrix, float** transposed0, float** transposed1, float** transposed2, float** transposed3, int n) {
    double start, end;
    int symmetric=0;

    printf("\nRunning Serial Test...\n");
    start = omp_get_wtime();
    symmetric = checkSym(matrix, n);
    if (!symmetric) {
        matTranspose(matrix, transposed1, n);
        end = omp_get_wtime();
    }else{
        printf("Matrix is Symmetric");
    }
    
    printf("Serial test took   %.6lf seconds.\n", (end - start));
//////////////////////////////////////////////////////////////////////////////////////
    printf("\nRunning Implicit Test...\n");
    start = omp_get_wtime();
    symmetric = checkSymImp(matrix, n);
    if (!symmetric) {
        matTransposeImp(matrix, transposed2, n);
        end = omp_get_wtime();
    }else{
        printf("Matrix is Symmetric");
    }
    
    printf("Implicit test took %.6lf seconds.\n", (end - start));
//////////////////////////////////////////////////////////////////////////////////////
    printf("\nRunning Explicit Test...\n");
    start = omp_get_wtime();
    symmetric = checkSymOMP(matrix, n);
    if (!symmetric) {
        matTransposeOMP(matrix, transposed3, n);
        end = omp_get_wtime();
    }else{
        printf("Matrix is Symmetric");
    }
    
    printf("Explicit test took %.6lf seconds.\n", (end - start));
//////////////////////////////////////////////////////////////////////////////////////
    printf("\nRunning ExplicitBlock Test...\n");
    start = omp_get_wtime();
    symmetric = checkSymOMPblock(matrix, n);
    if (!symmetric) {
        matTransposeOMPblock(matrix, transposed0, n);
        end = omp_get_wtime();
    }else{
        printf("Matrix is Symmetric");
    }
    
    printf("Explicit block test took %.6lf seconds.\n", (end - start));
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int p = atoi(argv[1]);
        int n = pow(2, p);

        float** matrix = createMatrix(n);
        float** transposed0 = createMatrix(n);
        float** transposed1 = createMatrix(n);
        float** transposed2 = createMatrix(n);
        float** transposed3 = createMatrix(n);

        initializeMatrix(matrix, n);
        resetMatrix(transposed0,n);
        resetMatrix(transposed1,n);
        resetMatrix(transposed2,n);
        resetMatrix(transposed3,n);

//        printf("//////////////////////////////////////////////////////////\n");
//        printMatrix(matrix,n);
//        printTransp(transposed0,n);
//        printTransp(transposed1,n);
//        printTransp(transposed2,n);
//        printTransp(transposed3,n);
        printf("//////////////////////////////////////////////////////////\n");

        if (argc == 2) {
            runAllTests(matrix, transposed0, transposed1, transposed2, transposed3, n);
    
            int check0and3 = compareChecksums(transposed1, transposed3, n, 2);
            int check0and2 = compareChecksums(transposed1, transposed3, n, 2);
            int check0and1 = compareChecksums(transposed1, transposed3, n, 2);
            int check1and3 = compareChecksums(transposed1, transposed3, n, 2);
            int check1and2 = compareChecksums(transposed1, transposed2, n, 2);
            int check2and3 = compareChecksums(transposed2, transposed3, n, 2);
            if (check1and3 && check1and2 && check2and3 && check0and3 && check0and2 && check0and1) {
                printf("The matrixes are equivalent\n\n");
                printf("//////////////////////////////////////////////////////////\n");
            }else{
                printf("\nThe matrixes are NOT equivalent\n");
            }

        } else {
            double start, end;
            int symmetric;

            if (strcmp(argv[2], "serial") == 0) {
                start = omp_get_wtime();
                symmetric = checkSym(matrix, n);
                if (!symmetric) {
                    matTranspose(matrix, transposed1, n);
                }
                end = omp_get_wtime();
                if (symmetric) printf("Matrix is Symmetric\n");
//                printf("Transposed\n");
//                printTransp(transposed1,n);
                printf("Serial operation took \n%.6lf\n", (end - start));
            } else if (strcmp(argv[2], "implicit") == 0) {
                start = omp_get_wtime();
                symmetric = checkSymImp(matrix, n);
                if (!symmetric) {
                    matTransposeImp(matrix, transposed2, n);
                }
                end = omp_get_wtime();
                if (symmetric) printf("Matrix is Symmetric\n");
//                printf("Transposed\n");
//                printTransp(transposed2,n);
                printf("Implicit operation took \n%.6lf\n", (end - start));
            } else if (strcmp(argv[2], "explicit") == 0) {
                start = omp_get_wtime();
                symmetric = checkSymOMP(matrix, n);
                if (!symmetric) {
                    matTransposeOMP(matrix, transposed3, n);
                }
                end = omp_get_wtime();
                if (symmetric) printf("Matrix is Symmetric\n");
//                printf("Transposed\n");
//                printTransp(transposed3,n);
                printf("Explicit operation took \n%.6lf\n", (end - start));
            } else if (strcmp(argv[2], "explicitblock") == 0) {
                start = omp_get_wtime();
                symmetric = checkSymOMPblock(matrix, n);
                if (!symmetric) {
                    matTransposeOMPblock(matrix, transposed0, n);
                }
                end = omp_get_wtime();
                if (symmetric) printf("Matrix is Symmetric\n");
//                printf("Transposed\n");
//                printTransp(transposed0,n);
                printf("Explicit Block operation took \n%.6lf\n", (end - start));
            } else {
                printf("Invalid mode specified\n");
                return 1;
            }
        }

        freeMatrix(matrix, n);
        freeMatrix(transposed0, n);
        freeMatrix(transposed1, n);
        freeMatrix(transposed2, n);
        freeMatrix(transposed3, n);
    } else {
        printf("\nInvalid mode specified\n\n");
        return 1;
    }
    return 0;
}
