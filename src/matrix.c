#include <global.h>

int SparseMatrix(int** M, int** S, int* D){
    int rows = D[0];
    int cols = D[1];
    int max_dim = (rows > cols) ? rows : cols;
    int count = 0;

    for(int i = 0; i < rows && count < max_dim; i++){
        for(int j = 0; j < cols && count < max_dim; j++){
            if(M[i][j]){
                S[0][count] = i;
                S[1][count] = j;
                S[2][count] = M[i][j];
                count++;
            }
        }
    }

    for(int i = count; i < max_dim; i++){
        S[0][i] = 0;
        S[1][i] = 0;
        S[2][i] = 0;
    }

    return (count < max_dim) ? count : -1;
}

int Addition(int** M, int** N, int** A, int* D){
    int rowsM = D[0], colsM = D[1];
    int rowsN = D[2], colsN = D[3];
    int rowsA = D[4], colsA = D[5];
    int overlapRows = (rowsM < rowsN) ? rowsM : rowsN;
    int overlapCols = (colsM < colsN) ? colsM : colsN;

    for(int i = 0; i < rowsA; i++)
        for(int j = 0; j < colsA; j++)
            A[i][j] = 0;

    for(int i = 0; i < overlapRows; i++){
        for(int j = 0; j < overlapCols; j++){
            if(i < rowsA && j < colsA){
                A[i][j] = M[i][j] + N[i][j];
            }
        }
    }

    if(rowsM == rowsN && colsM == colsN){
        return (rowsA == rowsM && colsA == colsM) ? 1 : 2;
    }
    
    return (overlapRows <= rowsA && overlapCols <= colsA) ? -1 : -2;
}

int Multiplication(int** M, int** N, int** A, int* D) {
    int rowsM = D[0], colsM = D[1];
    int rowsN = D[2], colsN = D[3];
    int rowsA = D[4], colsA = D[5];
    
    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < colsA; j++)
            A[i][j] = 0;

    if (colsM != rowsN) {
        for (int i = 0; i < colsN; i++)
            for (int j = colsM; j < rowsN; j++)
                N[j][i] = 0;
    }

    int colsM2 = (colsM < rowsN) ? colsM : rowsN;
    for (int i = 0; i < rowsM; i++) {
        for (int j = 0; j < colsN; j++) {
            for (int k = 0; k < colsM2; k++) {
                if (i < rowsA && j < colsA) {
                    A[i][j] += M[i][k] * N[k][j];
                }
            }
        }
    }
    
    if (rowsA == rowsM && colsA == colsN) {
        return 1;
    } else if (rowsA >= rowsM && colsA >= colsN) {
        return (colsM == rowsN) ? 2 : -1;
    }
    return -2;
}

int Transpose(int** A, int** AT, int* D) {
    int rows = (D[0] < D[3]) ? D[0] : D[3];
    int cols = (D[1] < D[2]) ? D[1] : D[2];

    for (int i = 0; i < D[2]; i++) {
        for (int j = 0; j < D[3]; j++) {
            AT[i][j] = (i < cols && j < rows) ? A[j][i] : 0;
        }
    }

    return (D[2] == D[1] && D[3] == D[0]) ? 1 : (D[2] >= D[1] && D[3] >= D[0] ? 2 : -1);
}

// Helper functions for Testing
int** initializeMatrix(int n, int m, int* values){
    int** ret = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        ret[i] = (int*)malloc(m*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ret[i][j] = values[i*m+j];
        }
    }
    return ret;
}

void freeMatrix(int n, int** M){
    for(int i=0; i<n; i++){
        free(M[i]);
    }
    free(M);
}