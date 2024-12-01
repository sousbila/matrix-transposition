#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <string.h>
#include "utils.h"
#include "explicit.h"
#include "explicit1.h"
#include "explicit2.h"
#include "explicit3.h"

void runAllTests(float** matrix, float** transposed0, float** transposed1, float** transposed2, float** transposed3, int n) {
    double start, end;
    int symmetric=0;

    printf("\nRunning Explicit 0 Test...");
    start = omp_get_wtime();
    symmetric = checkSymOMP(matrix, n);
    if (!symmetric) {
        matTransposeOMP(matrix, transposed3, n);
        end = omp_get_wtime();
        resetMatrix(transposed0,n);
    }else{
        printf("Matrix is Symmetric");
    }
    
    printf("OMP 0 test took %.6lf seconds.\n", (end - start));
    
    printf("\n///////////////////////////////////////////////////////////////////////////");

    printf("\nRunning Explicit1 Test...");
    start = omp_get_wtime();
    symmetric = checkSymOMP1(matrix, n);
    if (!symmetric) {
        matTransposeOMP1(matrix, transposed1, n);
        end = omp_get_wtime();
    }else{
        printf("Matrix is Symmetric");
    }
    

    printf("OMP 1 test took   %.6lf seconds.\n", (end - start));

    printf("///////////////////////////////////////////////////////////////////////////");

    printf("\nRunning Explicit2 Test...");
    start = omp_get_wtime();
    symmetric = checkSymOMP2(matrix, n);
    if (!symmetric) {
        matTransposeOMP2(matrix, transposed2, n);
        end = omp_get_wtime();
    }else{
        printf("Matrix is Symmetric");
    }
    

    printf("OMP 2 test took %.6lf seconds.\n", (end - start));

    printf("///////////////////////////////////////////////////////////////////////////");

    printf("\nRunning Explicit3 Test...");
    start = omp_get_wtime();
    symmetric = checkSymOMP3(matrix, n);
    if (!symmetric) {
        matTransposeOMP3(matrix, transposed3, n);
        end = omp_get_wtime();
    }else{
        printf("Matrix is Symmetric");
    }
    
    printf("OMP 3 test took %.6lf seconds.\n", (end - start));
    
    printf("///////////////////////////////////////////////////////////////////////////");

    printf("\nRunning Explicit Again Test...");
    start = omp_get_wtime();
    symmetric = checkSymOMP(matrix, n);
    if (!symmetric) {
        matTransposeOMP(matrix, transposed3, n);
        end = omp_get_wtime();
    }else{
        printf("Matrix is Symmetric");
    }
    
    printf("OMP 0 test took %.6lf seconds.\n\n", (end - start));
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

        printf("\n\n//////////////////////////////////////////////////////////\n");

        if (argc == 2) {
            runAllTests(matrix, transposed0, transposed1, transposed2, transposed3, n);
    
            int check0and3 = compareChecksums(transposed1, transposed3, n, 2);
            int check0and2 = compareChecksums(transposed1, transposed3, n, 2);
            int check0and1 = compareChecksums(transposed1, transposed3, n, 2);
            int check1and3 = compareChecksums(transposed1, transposed3, n, 2);
            int check1and2 = compareChecksums(transposed1, transposed2, n, 2);
            int check2and3 = compareChecksums(transposed2, transposed3, n, 2);
            if (check1and3 && check1and2 && check2and3 && check0and3 && check0and2 && check0and1) {
                printf("\nThe matrixes are equivalent\n");
            }else{
                printf("\nThe matrixes are NOT equivalent\n");
            }

        } else {
            double start, end;
            int symmetric;

            if (strcmp(argv[2], "omp1") == 0) {
                start = omp_get_wtime();
                symmetric = checkSymOMP1(matrix, n);
                if (!symmetric) {
                    matTransposeOMP1(matrix, transposed1, n);
                }
                end = omp_get_wtime();
                if (symmetric) printf("Matrix is Symmetric\n");
                printf("OMP 1 operation took \n%.6lf", (end - start));
                
            } else if (strcmp(argv[2], "omp2") == 0) {
                start = omp_get_wtime();
                symmetric = checkSymOMP2(matrix, n);
                if (!symmetric) {
                    matTransposeOMP2(matrix, transposed2, n);
                }
                end = omp_get_wtime();
                if (symmetric) printf("Matrix is Symmetric\n");
                printf("OMP 2 operation took \n%.6lf", (end - start));
                
            } else if (strcmp(argv[2], "omp3") == 0) {
                start = omp_get_wtime();
                symmetric = checkSymOMP3(matrix, n);
                if (!symmetric) {
                    matTransposeOMP3(matrix, transposed3, n);
                }
                end = omp_get_wtime();
                if (symmetric) printf("Matrix is Symmetric\n");
                printf("OMP 3 operation took \n%.6lf", (end - start));
                
            } else if (strcmp(argv[2], "omp") == 0) {
                start = omp_get_wtime();
                symmetric = checkSymOMP(matrix, n);
                if (!symmetric) {
                    matTransposeOMP(matrix, transposed0, n);
                }
                end = omp_get_wtime();
                if (symmetric) printf("Matrix is Symmetric\n");
                printf("OMP 0 operation took \n%.6lf", (end - start));
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
