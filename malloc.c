#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    // ======================================================================== 
    // Normal variable
    message_line("Normal variable");
    int a0 = 42;
    int *a1 = &a0;
    printf("address a0: %p,  value a0: %d\n", &a0, a0);
    printf("address a1: %p,  value a1: %p, dereferenced a1: %d\n", &a1, a1, *a1);

    // ======================================================================== 
    // Single variable in the heap.
    message_line("Single variable on the heap");
    int *b0 = (int*) malloc(sizeof(int));
    *b0 = 10;
    printf("address b0: %p,  value b0: %p, dereferenced b0: %d\n", &b0, b0, *b0);
    free(b0);
    b0 = NULL;


    const int N=4;
    // ======================================================================== 
    // Block of memory in the heap of type int.
    message_line("Block of memory in the heap of type int");
    int *c0 = (int*) malloc(sizeof(int)*N);
    for (int i=0; i<N; i++) {
        c0[i] = 101 + i;
        // Address increments with 4 bytes.
        printf("address c0[%d]: %p,  value c0[%d]: %d\n", i, &c0[i], i, c0[i]);
    }
    // Get value of 3rd element by dereferencing pointer to the start of the block + 3.
    printf("3rd element of c0 = %d\n", *(c0+2));
    // Get value of 3rd element by array notation.
    printf("3rd element of c0 = %d\n", c0[2]);
    printf("address c0: %p,  value c0: %p, dereferenced c0: %d\n", &c0, c0, *c0);
    // Free  the memory block.
    free(c0);
    // Clear the stored memory address. (Not strictly needed.)
    c0 = NULL;

    // ======================================================================== 
    // Block of memory in the heap of type long. 
    message_line("Block of memory in the heap of type long");
    long *d0 = (long*) malloc(sizeof(long)*N);
    for (int i=0; i<N; i++) {
        d0[i] = 201 + i;
        // Address increments with 8 bytes.
        printf("address d0[%d]: %p,  value d0[%d]: %ld\n", i, &d0[i], i, d0[i]);
    }
    printf("address d0: %p,  value d0: %p, dereferenced d0: %ld\n", &d0, d0, *d0);
    // Free  the memory block.
    free(d0);
    // Clear the stored memory address. (Not strictly needed.)
    d0 = NULL;




    exit(EXIT_SUCCESS);
}
