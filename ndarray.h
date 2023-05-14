#ifndef __NDARRAY
#define __NDARRAY

#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct {
    int ndim;
    int size;
    int bytes;
    int *shape;
    int *strides;
    data_t *data;
} NDArray;

void ndarray_init(NDArray *a, int shape[], int ndim);

void ndarray_free(NDArray *a);

void ndarray_copy(NDArray *dst, NDArray *src);

void ndarray_info(NDArray *a);

data_t ndarray_max(NDArray *a);

int ndarray_argmax(NDArray *a);

void ndarray_print(NDArray *a);

void _print_vec(int* v, int ndim, char* label);

#endif
