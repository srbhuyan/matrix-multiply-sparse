#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Represent sparse matrices in cooridnate format
typedef struct {
    int row;
    int col;
    int value;
} SparseMatrix;

// Create sparse matrix from user given matrix and return count of non-zero elements
int createSparseMatrix(int rows, int cols, int matrix[rows][cols], SparseMatrix sparse[]) {
    int nz_count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse[nz_count].row = i;
                sparse[nz_count].col = j;
                sparse[nz_count].value = matrix[i][j];
                nz_count++;
            }
        }
    }
    return nz_count;
}

// Multiply sparse matrices
void multiplySparseMatrices(SparseMatrix A[], int A_count, SparseMatrix B[], int B_count, SparseMatrix result[], int *result_count, int A_rows, int B_cols) {
    *result_count = 0; // only used for indexing so we know where the non-zero elements are
    for (int i = 0; i < A_count; i++) {
        for (int j = 0; j < B_count; j++) {
            if (A[i].col == B[j].row) {
                result[*result_count].row = A[i].row;
                result[*result_count].col = B[j].col;
                result[*result_count].value = A[i].value * B[j].value;
                (*result_count)++;
            }
        }
    }
}

// Function to print original matrix
void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}


void printSparseMatrix(SparseMatrix sparse[], int count) {
    printf("Row\tCol\tValue\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\t%d\n", sparse[i].row, sparse[i].col, sparse[i].value);
    }
}

// Function to generate a random sparse matrix
int generateRandomSparseMatrix(int rows, int cols, int matrix[rows][cols], int non_zero_count) {
    // Initialize all elements to zero
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }

    // Assign values to random positions
    for (int i = 0; i < non_zero_count; i++) {
        int rand_row = rand() % rows;
        int rand_col = rand() % cols;
        int rand_value = (rand() % 9) + 1; // Random values between 1 and 9
        matrix[rand_row][rand_col] = rand_value;
    }

    return non_zero_count;
}

// Generates two random *square* matrices of SIZE and creates an intermediate form to multiply them.
int main(int argc, char * argv[]) {

    if(argc < 2){
      printf("Usage: main <SIZE>\n");
      exit(0);
    }

    int SIZE = atoi(argv[1]);

    srand(time(0)); // seed

    int matrix1[SIZE][SIZE], matrix2[SIZE][SIZE];
    int MAT_SIZE = SIZE * SIZE;

    SparseMatrix sparseA[MAT_SIZE], sparseB[MAT_SIZE], result[MAT_SIZE];
    int A_count, B_count, result_count;

    // Generate two random sparse matrices with 15 non-zero elements each
    generateRandomSparseMatrix(SIZE, SIZE, matrix1, 15);
    generateRandomSparseMatrix(SIZE, SIZE, matrix2, 15);

    // Print the original matrices
    printf("Matrix 1:\n");
    printMatrix(SIZE, SIZE, matrix1);

    printf("\nMatrix 2:\n");
    printMatrix(SIZE, SIZE, matrix2);

    // Convert to sparse matrix format
    A_count = createSparseMatrix(SIZE, SIZE, matrix1, sparseA);
    B_count = createSparseMatrix(SIZE, SIZE, matrix2, sparseB);

    // Multiply
    multiplySparseMatrices(sparseA, A_count, sparseB, B_count, result, &result_count, SIZE, SIZE);

    // Print
    printf("Resultant Sparse Matrix:\n");
    printSparseMatrix(result, result_count);

    return 0;
}

