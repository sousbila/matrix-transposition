int checkSymOMPblock(float** matrix, int n) {
    int blockSize = 64;
    int symmetric = 1;

#pragma omp parallel for default(none) shared(matrix, n, blockSize) reduction(&& : symmetric)
    for (int ii = 0; ii < n; ii += blockSize) {
        for (int jj = ii; jj < n; jj += blockSize) {
            int imax = (ii + blockSize > n) ? n : ii + blockSize;
            int jmax = (jj + blockSize > n) ? n : jj + blockSize;

            for (int i = ii; i < imax; i++) {
                if (!symmetric) continue;
                int jStart = (i == ii) ? i + 1 : jj;
                int limit = jmax - ((jmax - jStart) % 4);
                int j;
                for (j = jStart; j < limit; j += 4) {
                    if (matrix[i][j] != matrix[j][i] ||
                        matrix[i][j+1] != matrix[j+1][i] ||
                        matrix[i][j+2] != matrix[j+2][i] ||
                        matrix[i][j+3] != matrix[j+3][i]) {
                        symmetric = 0;
                    }
                }
                for (; j < jmax; j++) {
                    if (matrix[i][j] != matrix[j][i]) {
                        symmetric = 0;
                    }
                }
            }
        }
    }
    return symmetric;
}

void matTransposeOMPblock(float** matrix, float** transposed, int n) {
    int blockSize = 64;

#pragma omp parallel for default(none) shared(matrix, transposed, n, blockSize)
    for (int ii = 0; ii < n; ii += blockSize) {
        for (int jj = 0; jj < n; jj += blockSize) {
            int imax = (ii + blockSize > n) ? n : ii + blockSize;
            int jmax = (jj + blockSize > n) ? n : jj + blockSize;

            for (int i = ii; i < imax; i++) {
                int limit = jmax - ((jmax - jj) % 4);
                int j;
                for (j = jj; j < limit; j += 4) {
                    transposed[j][i]     = matrix[i][j];
                    transposed[j+1][i]   = matrix[i][j+1];
                    transposed[j+2][i]   = matrix[i][j+2];
                    transposed[j+3][i]   = matrix[i][j+3];
                }
                for (; j < jmax; j++) {
                    transposed[j][i] = matrix[i][j];
                }
            }
        }
    }
}