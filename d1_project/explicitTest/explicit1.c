int checkSymOMP1(float** matrix, int n) {
    int blockSize = 64;
    int symmetric = 1;

    #pragma omp parallel for default(none) shared(matrix, n, blockSize) reduction(&& : symmetric)
    for (int ii = 0; ii < n; ii += blockSize) {
        for (int jj = ii; jj < n; jj += blockSize) {
            int iMax = (ii + blockSize > n) ? n : ii + blockSize;
            int jMax = (jj + blockSize > n) ? n : jj + blockSize;

            for (int i = ii; i < iMax; i++) {
                if (!symmetric) continue;
                int jStart = (i == ii) ? i + 1 : jj;
                for (int j = jStart; j < jMax; j++) {
                    if (matrix[i][j] != matrix[j][i]) {
                        symmetric = 0;
                    }
                }
            }
        }
    }
    return symmetric;
}

void matTransposeOMP1(float** matrix, float** transposed, int n) {
    int blockSize = 64;

    #pragma omp parallel for default(none) shared(matrix, transposed, n, blockSize)
    for (int ii = 0; ii < n; ii += blockSize) {
        for (int jj = 0; jj < n; jj += blockSize) {
            int iMax = (ii + blockSize > n) ? n : ii + blockSize;
            int jMax = (jj + blockSize > n) ? n : jj + blockSize;

            for (int i = ii; i < iMax; i++) {
                for (int j = jj; j < jMax; j++) {
                    transposed[j][i] = matrix[i][j];
                }
            }
        }
    }
}