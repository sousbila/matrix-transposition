int checkSymImp(float** matrix, int n) {
    int blockSize = 64;

    for (int ii = 0; ii < n; ii += blockSize) {
        int imax = (ii + blockSize > n) ? n : ii + blockSize;
        for (int jj = 0; jj <= ii; jj += blockSize) {
            int jmax = (jj + blockSize > n) ? n : jj + blockSize;
            for (int i = ii; i < imax; i++) {
                int jStart = (jj == ii) ? i + 1 : jj;
                for (int j = jStart; j < jmax; j++) {
                    if (matrix[i][j] != matrix[j][i]) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

void matTransposeImp(float** matrix, float** transposed, int n) {
    int blockSize = 64;

    for (int ii = 0; ii < n; ii += blockSize) {
        int imax = (ii + blockSize > n) ? n : ii + blockSize;
        for (int jj = 0; jj < n; jj += blockSize) {
            int jmax = (jj + blockSize > n) ? n : jj + blockSize;
            for (int i = ii; i < imax; i++) {
                for (int j = jj; j < jmax; j++) {
                    transposed[j][i] = matrix[i][j];
                }
            }
        }
    }
}
