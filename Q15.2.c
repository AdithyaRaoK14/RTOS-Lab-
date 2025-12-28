// Q15 Child Program 1: Calculate row sum of a matrix
// File: q15_child_matrix.c

#include <stdio.h>
#include <unistd.h>

int main() {
    int rows, cols, i, j;
    
    printf("=== Matrix Row Sum Program ===\n");
    printf("Child Process PID: %d\n\n", getpid());
    
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    
    int matrix[rows][cols];
    int rowSum[rows];
    
    printf("\nEnter matrix elements:\n");
    for (i = 0; i < rows; i++) {
        rowSum[i] = 0;
        for (j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
            rowSum[i] += matrix[i][j];
        }
    }
    
    printf("\nMatrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\nRow Sums:\n");
    for (i = 0; i < rows; i++) {
        printf("Row %d sum: %d\n", i, rowSum[i]);
    }
    
    return 0;
}

// Compile: gcc -o q15_child_matrix q15_child_matrix.c