// Create, edit, delete multidimensional array.
//
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int rows = 4;
    const int cols = 4;

    // allocate memory
    int **a = (int **)malloc(sizeof(int *) * rows);
    for (int i = 0; i < cols; i++) {
        a[i] = (int *)malloc(sizeof(int) * cols);
    }

    // set dummy values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            a[i][j] = i * rows + j;
        }
    }

    // print values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    // free memory
    for (int i = 0; i < rows; i++) {
        free(a[i]);
    }
    free(a);
}
