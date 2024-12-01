int checkSym(float** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) return 0;
        }
    }
    return 1;
}

void matTranspose(float** matrix, float** transposed, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
}