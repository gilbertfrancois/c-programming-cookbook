// Create, edit, delete multidimensional array using struct and functions.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Set NDArray data type
typedef int data_t;

// Define the NDArray
typedef struct {
    data_t **data;
    int rows;
    int cols;
} NDArray;

void alloc_ndarray(NDArray *array, const int rows, const int cols) {
    array->rows = rows;
    array->cols = cols;
    array->data = (data_t **)malloc(sizeof(data_t *) * rows);
    // allocate memory
    for (int i = 0; i < cols; i++) {
        array->data[i] = (data_t *)malloc(sizeof(data_t) * cols);
    }
    // fill with some dummy data
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array->data[i][j] = i * rows + j;
        }
    }
}

void copy_ndarray(NDArray *src, NDArray *dst) {
    // Make a shallow copy of the struct.
    memcpy(dst, src, sizeof(*src));
}

void deep_copy_ndarray(NDArray *src, NDArray *dst) {
    // Make a deep copy of the struct.
    dst->rows = src->rows;
    dst->cols = src->cols;
    dst->data = (data_t **)malloc(sizeof(data_t *) * src->rows);
    for (int i = 0; i < src->rows; i++) {
        dst->data[i] = (data_t *)malloc(sizeof(data_t) * src->cols);
        memcpy(dst->data[i], src->data[i], sizeof(data_t) * src->cols);
    }
}

void print_ndarray(NDArray *array) {
    // print values to the console
    for (int i = 0; i < array->rows; i++) {
        for (int j = 0; j < array->cols; j++) {
            printf("%4d ", array->data[i][j]);
        }
        printf("\n");
    }
}

void free_ndarray(NDArray *array) {
    // free memory that was created inside the struct NDArray.
    for (int i = 0; i < array->rows; i++) {
        free(array->data[i]);
    }
    free(array->data);
}

int main(int argc, char *argv[]) {
    const int rows = 4;
    const int cols = 4;
    printf("---[ allocated on the stack ]-----\n");
    NDArray array;
    alloc_ndarray(&array, rows, cols);
    print_ndarray(&array);
    free_ndarray(&array);
    printf("\n");

    printf("---[ allocated on in the heap ]---\n");
    NDArray *ptr_array = (NDArray *)malloc(sizeof(NDArray));
    alloc_ndarray(ptr_array, rows, cols);
    print_ndarray(ptr_array);
    free_ndarray(ptr_array);
    free(ptr_array);
    printf("\n");

    printf("---[ shallow copy ]---------------\n");
    const int rows2 = 5;
    const int cols2 = 5;
    NDArray *ptr_src2 = (NDArray *)malloc(sizeof(NDArray));
    alloc_ndarray(ptr_src2, rows2, cols2);
    NDArray *ptr_dst2 = (NDArray *)malloc(sizeof(NDArray));
    copy_ndarray(ptr_src2, ptr_dst2);
    print_ndarray(ptr_dst2);
    // Important: for shallow copies, only free the data arrays from the
    // src! The dst has no allocated memory for the data arrays of its own. 
    free_ndarray(ptr_src2);
    free(ptr_dst2);
    free(ptr_src2);

    printf("---[ deep copy ]------------------\n");
    const int rows3 = 3;
    const int cols3 = 3;
    NDArray *ptr_src3 = (NDArray *)malloc(sizeof(NDArray));
    alloc_ndarray(ptr_src3, rows3, cols3);
    NDArray *ptr_dst3 = (NDArray *)malloc(sizeof(NDArray));
    deep_copy_ndarray(ptr_src3, ptr_dst3);
    print_ndarray(ptr_dst3);
    free_ndarray(ptr_src3);
    free(ptr_src3);
    free_ndarray(ptr_dst3);
    free(ptr_dst3);

    return 0;
}
