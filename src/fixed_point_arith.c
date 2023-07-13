#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void float2fixed(float f, int16_t *fixed, uint8_t frac) {
    *fixed = (int16_t)(f * (1 << frac));
}

void fixed2float(int16_t fixed, float *f, uint8_t frac) {
    *f = (float)fixed / (1 << frac);
}

void test_float2fixed(float f, uint8_t frac, float eps) {
    int16_t fixed = 0;
    float2fixed(f, &fixed, frac);
    float f2 = 0;
    fixed2float(fixed, &f2, frac);
    float err = fabs(f - f2);
    if (err < eps) {
        printf("[PASSED] err: %f, ", err);
    }
    else {
        printf("[FAILED] err: %f, ", err);
    }
    printf("float: %0.8f, fixed: %d, frac: %d, float2: %0.8f\n", f, fixed, frac, f2);
}

void test_fixed2float(int16_t fixed, uint8_t frac, float eps) {
    float f = 0;
    int16_t fixed2 = 0;
    int16_t epsi = (int16_t) (eps * (1 << frac));
    fixed2float(fixed, &f, frac);
    float2fixed(f, &fixed2, frac);
    int16_t err = abs(fixed - fixed2); 
    if (err < epsi) {
        printf("[PASSED] err: %d, ", err);
    }
    else {
        printf("[FAILED] err: %d, ", err);
    }
    printf("float: %10.8f, fixed: %d, frac: %d, fixed2: %10.8d\n", f, fixed, frac, fixed2);
}


void print_float_fixed(float f, int16_t fixed, uint8_t frac) {
    printf("float: %f, fixed: %d, frac: %d\n", f, fixed, frac);
}

int main(int argc, char *argv[]) {

    uint8_t prec = 16;
    uint8_t frac = 11;
    /* uint16_t frac_mask = (1 << frac) - 1; */
    uint8_t dec = prec - frac;

    printf("max decimal: %d\n", (int)((1 << (dec - 1)) - 1));
    printf("min decimal: %d\n", (int)(-1 * (1 << (dec - 1))));
    printf("max fraction: %d\n", (int)(1 << frac));
    printf("min fraction: %f\n", 1.0f/((1 << frac)-1));

    for (int i=0; i<10; i++) {
        float val = 20*(float)rand() / RAND_MAX - 10;
        test_float2fixed(val, frac, 1.0f/(1 << frac));
    }   

    for (int i=0; i<10; i++) {
        int16_t val = UINT16_MAX*(float)rand() / RAND_MAX - INT16_MAX;
        test_fixed2float(val, frac, 1.0f/(1 << frac));
    }   

    int16_t pi_c = 25664;
    float pi = 0;
    fixed2float(pi_c, &pi, frac);
    printf("pi: %f\n", pi);

    float one_f = 0.1f;
    int16_t one_i = 0;
    float2fixed(one_f, &one_i, frac);
    int ans_i = one_i * one_i;
    float ans_f = 0;
    fixed2float(ans_i, &ans_f, frac);
    printf("ans: %f\n", ans_f);

    return 0;
}
