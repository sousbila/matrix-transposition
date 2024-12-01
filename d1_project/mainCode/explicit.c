int checkSymOMP(float** matrix, int n) {
    int symmetric = 1; 

#pragma omp parallel for reduction(&& : symmetric) default(none) shared(matrix, n)
    for (int i = 0; i < n; i++) {
        if (!symmetric) continue;
        for (int j = i + 1; j < n; j++) { 
            if (matrix[i][j] != matrix[j][i]) {
                symmetric = 0; 
            }
        }
    }

    return symmetric;
}

void matTransposeOMP(float** matrix, float** transposed, int n) {
#pragma omp parallel for collapse(2) default(none) shared(matrix, transposed, n)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
}