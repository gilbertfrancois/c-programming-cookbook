#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    // typedef char                    __int8_t;
    const unsigned long int i8_1 = sizeof(char);
    // typedef unsigned char           __uint8_t;
    const unsigned long int i8_2 = sizeof(unsigned char);
    // typedef short                   __int16_t;
    const unsigned long int i16_1 = sizeof(short);
    // typedef unsigned short          __uint16_t;
    const unsigned long int i16_2 = sizeof(unsigned short);
    // typedef int                     __int32_t;
    const unsigned long int i32_1 = sizeof(int);
    // typedef unsigned int            __uint32_t;
    const unsigned long int i32_2 = sizeof(unsigned int);
    // typedef long long               __int64_t;
    const unsigned long int i64_1 = sizeof(long);
    const unsigned long int i64_2 = sizeof(long long);
    // typedef unsigned long long      __uint64_t;
    const unsigned long int i64_3 = sizeof(unsigned long);
    const unsigned long int i64_4 = sizeof(unsigned long long);

    const unsigned long int a5 = sizeof(float);
    const unsigned long int a6 = sizeof(double);
    const unsigned long int a7 = sizeof(long double);


    printf("---[ sizeof(type) ]-----------------\n");
    printf("%20s: %lu byte, %lu bit\n", "char", i8_1, i8_1 * 8);
    printf("%20s: %lu byte, %lu bit\n", "unsigned char", i8_2, i8_2 * 8);

    printf("%20s: %lu byte, %lu bit\n", "short", i16_1, i16_1 * 8);
    printf("%20s: %lu byte, %lu bit\n", "unsigned short", i16_2, i16_2 * 8);

    printf("%20s: %lu byte, %lu bit\n", "int", i32_1, i32_1 * 8);
    printf("%20s: %lu byte, %lu bit\n", "unsigned int", i32_2, i32_2 * 8);

    printf("%20s: %lu byte, %lu bit\n", "long", i64_1, i64_1 * 8);
    printf("%20s: %lu byte, %lu bit\n", "long long", i64_2, i64_2 * 8);

    printf("%20s: %lu byte, %lu bit\n", "unsigned long", i64_3, i64_3 * 8);
    printf("%20s: %lu byte, %lu bit\n", "unsigned long long", i64_4, i64_4 * 8);

    printf("%20s: %lu byte, %lu bit\n", "float", a5, a5 * 8);
    printf("%20s: %lu byte, %lu bit\n", "double", a6, a6 * 8);
    printf("%20s: %lu byte, %lu bit\n", "long double", a7, a7 * 8);

    printf("---[ sizeof(pointer) ]---------------\n");
    const int p0 = 1;
    int* p1 = (int*)malloc(sizeof(int));

    printf("%20s: %lu byte, %lu bit, %p\n", "stack pointer", sizeof(&p0), sizeof(&p0)*8, &p0);
    printf("%20s: %lu byte, %lu bit, %p\n", "heap pointer", sizeof(p1), sizeof(p1)*8, p1);

    free(p1);

    return 0;
}
