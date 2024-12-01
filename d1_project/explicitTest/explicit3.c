int checkSymOMP3(float** matrix, int n) {
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
                int limit = jMax - ((jMax - jStart) % 4);
                int j;
                #pragma omp simd
                for (j = jStart; j < limit; j += 4) {
                    if (matrix[i][j] != matrix[j][i] ||
                        matrix[i][j+1] != matrix[j+1][i] ||
                        matrix[i][j+2] != matrix[j+2][i] ||
                        matrix[i][j+3] != matrix[j+3][i]) {
                        symmetric = 0;
                    }
                }
                for (; j < jMax; j++) {
                    if (matrix[i][j] != matrix[j][i]) {
                        symmetric = 0;
                    }
                }
            }
        }
    }
    return symmetric;
}

void matTransposeOMP3(float** matrix, float** transposed, int n) {
    int blockSize = 64;

    #pragma omp parallel for default(none) shared(matrix, transposed, n, blockSize)
    for (int jj = 0; jj < n; jj += blockSize) {
        for (int ii = 0; ii < n; ii += blockSize) {
            int iMax = (ii + blockSize > n) ? n : ii + blockSize;
            int jMax = (jj + blockSize > n) ? n : jj + blockSize;

            for (int j = jj; j < jMax; j++) {
                #pragma omp simd
                for (int i = ii; i < iMax; i++) {
                    transposed[j][i] = matrix[i][j];
                }
            }
        }
    }
}