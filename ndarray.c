#include "ndarray.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void ndarray_init(NDArray *a, int shape[], int ndim) {
    a->ndim = ndim;
    // Create shape array.
    a->shape = (int *)malloc(ndim * sizeof(int));
    memcpy(a->shape, shape, ndim * sizeof(int));
    // Create strides array.
    a->strides = (int *)malloc(ndim * sizeof(int));
    // Compute size and strides.
    unsigned long size = 1;
    for (int i = a->ndim - 1; i > -1; i--) {
        a->strides[i] = size;
        size *= a->shape[i];
    }
    a->size = size;
    // Compute size in bytes.
    a->bytes = size * sizeof(data_t);

    // Alloc and init data buffer.
    a->data = (data_t *)malloc(a->size * sizeof(data_t));
    // Set all bytes to zero, to prevent crappy data.
    // Note that memset works on bytes, not on int.
    memset(a->data, 0, a->size * sizeof(a->data[0]));
    ndarray_info(a);
}

void ndarray_info(NDArray *a) {
    _print_vec(a->shape, a->ndim, "shape");
    printf(", ");
    _print_vec(a->strides, a->ndim, "strides");
    printf(", size=%lu", a->size);
    printf(", bytes=%lu", a->bytes);
    printf(", dtype=int");
    printf("\n");
}

data_t ndarray_max(NDArray *a) {
    data_t max = INT_MIN;
    for (int i=0; i<a->size; i++) {
        if (a->data[i] > max) {
            max = a->data[i];
        }
    }
    return max;
}

int ndarray_argmax(NDArray *a) {
    data_t max = INT_MIN;
    int argmax = -1;
    for (int i=0; i<a->size; i++) {
        if (a->data[i] > max) {
            max = a->data[i];
            argmax = i;
        }
    }
    return argmax;
}

void ndarray_print(NDArray *a) {
    // Determine the max number for better alignment.
    int max = ndarray_max(a);
    // Create the format string.
    char fmt1[12];
    sprintf(fmt1, "%d", max);
    unsigned long n_digits = strlen(fmt1);
    char fmt2[12];
    sprintf(fmt2, "%%%lud ", n_digits);

    if (a->ndim == 2) {
        for (int i = 0; i < a->shape[0]; i++) {
            for (int j = 0; j < a->shape[1]; j++) {
                int *s = a->strides;
                int index = s[0] * i + s[1] * j;
                // printf("%d ", a->data[index]);
                printf(fmt2, a->data[index]);
                a->data[index] = index;
            }
            printf("\n");
        }
    }
    else {
        for (int i = 0; i < a->size; i++) {
            printf("%d ", a->data[i]);
        }
        printf("\n");
    }
}

void _print_vec(int *v, int ndim, char *label) {
    printf("%s=(", label);
    for (int i = 0; i < ndim - 1; i++)
        printf("%d, ", v[i]);
    printf("%d)", v[ndim - 1]);
}

void test_2D() {
    NDArray *array = (NDArray *)malloc(sizeof(NDArray));
    const int rows = 5;
    const int cols = 5;
    int shape[] = {rows, cols};
    ndarray_init(array, shape, 2);
    ndarray_print(array);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int *s = array->strides;
            int index = s[0] * i + s[1] * j;
            array->data[index] = index;
        }
    }
    ndarray_print(array);
}

void test_4D() {
    NDArray *array = (NDArray *)malloc(sizeof(NDArray));
    const int samples = 2;
    const int rows = 5;
    const int cols = 4;
    const int chan = 3;
    int shape[] = {samples, rows, cols, chan};
    ndarray_init(array, shape, 4);
    ndarray_print(array);
    for (int n = 0; n < samples; n++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int k = 0; k < chan; k++) {
                    int *s = array->strides;
                    int index = s[0] * n + s[1] * i + s[2] * j + s[3] * k;
                    array->data[index] = index;
                }
            }
        }
    }
    ndarray_print(array);
}

int main(int argc, char *argv[]) {
    test_2D();
    return 0;
}
