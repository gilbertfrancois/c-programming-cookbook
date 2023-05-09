#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;

typedef struct {
    int ndim;
    int *shape;
    int *strides;
    data_t *data;
} NDArray;

void ndarray_init(NDArray *a, int shape[], int ndim) {
    a->shape = (int*)malloc(ndim*sizeof(int));
    memcpy(a->shape, shape, ndim*sizeof(int));
    a->strides = (int*)malloc(ndim*sizeof(int));
    
    printf("%d\n", shape[0]);
    printf("%d\n", shape[1]);
    printf("%d\n", shape[2]);
    printf("%d\n", shape[3]);
    printf("%d\n", a->shape[0]);
    printf("%d\n", a->shape[1]);
    printf("%d\n", a->shape[2]);
    printf("%d\n", a->shape[3]);
}


int main(int argc, char* argv[]) {
    NDArray *array = (NDArray*)malloc(sizeof(NDArray));

    int shape[] = {1, 40, 30, 3};
    ndarray_init(array, shape, 4);


    return 0;
}

