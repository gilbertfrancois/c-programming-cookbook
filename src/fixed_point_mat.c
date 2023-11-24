#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define FRAC 10
#define HALF_FIXP (1 << (FRAC - 1))
#define RTOL 0.05

typedef struct {
    int a; // alpha
    int b; // beta
    int c; // gamma
} rot3;

void float2fixed(float f, int16_t *fixed) {
    *fixed = (int16_t)(f * (1 << FRAC));
}

void fixed2float(int16_t fixed, float *f, uint8_t frac) {
    *f = (float)fixed / (1 << FRAC);
}

void int2fixed(int i, int *fixed) { *fixed = i << FRAC; }
void fixed2int(int fixed, int *i) { *i = (fixed + HALF_FIXP)  >> FRAC; }


int mulfp(int a, int b) { return (a * b) >> FRAC; }
int divfp(int a, int b) { return (a << FRAC) / b; }

/* int calc_x(int x, int y, int z, rot3 *r) { */
/*     const int rx = mulfp(coslu[r->a], coslu[r->b]); */
/*     const int ry = mulfp(mulfp(coslu[r->a], sinlu[r->b]), sinlu[r->c]) - */
/*              mulfp(sinlu[r->a], coslu[r->c]); */
/*     const int rz = mulfp(sinlu[r->a], sinlu[r->c]) + */
/*              mulfp(mulfp(coslu[r->a], sinlu[r->b]), coslu[r->c]); */
/*     const int ans = mulfp(x, rx) + mulfp(y, ry) + mulfp(z, rz); */
/*     return ans; */
/* } */

/* int calc_y(int x, int y, int z, rot3 *r) { */
/*     const int rx = mulfp(sinlu[r->a], coslu[r->b]); */
/*     const int ry = mulfp(coslu[r->a], coslu[r->c]) + */ 
/*              mulfp(mulfp(sinlu[r->a], sinlu[r->b]), sinlu[r->c]); */
/*     const int rz = mulfp(mulfp(sinlu[r->a], sinlu[r->b]), coslu[r->c])- */
/*              mulfp(coslu[r->a], sinlu[r->c]); */
/*     const int ans = mulfp(x, rx) + mulfp(y, ry) + mulfp(z, rz); */
/*     return ans; */
/* } */

/* int calc_z(int x, int y, int z, rot3 *r) { */
/*     const int rx = -sinlu[r->b]; */
/*     const int ry = mulfp(coslu[r->b], sinlu[r->c]); */
/*     const int rz = mulfp(coslu[r->b], coslu[r->c]); */
/*     const int ans = mulfp(x, rx) + mulfp(y, ry) + mulfp(z, rz); */
/*     return ans; */
/* } */

void test_mul(void) {
    float a_f = 0.0;
    float b_f = 0.0;
    int16_t a_i = 0;
    int16_t b_i = 0;
    printf("---[ test_mul ]---\n");
    for (int i=0; i<10; i++) {
        a_f = 2.0f*(float)rand() / (float)RAND_MAX - 1.0f;
        b_f = 2.0f*(float)rand() / (float)RAND_MAX - 1.0f;
        float2fixed(a_f, &a_i);
        float2fixed(b_f, &b_i);
        int16_t c_i = mulfp(a_i, b_i);
        float c_f = a_f * b_f;
        float c_i2f = 0.0f;
        fixed2float(c_i, &c_i2f, FRAC);
        float err = fabs(c_f - c_i2f);
        const float rtol = fabs(c_f * RTOL);
        if (err < rtol) {
            printf("[PASSED] err: %f, %f, ", err, rtol);
        } else {
            printf("[FAILED] err: %f, %f, ", err, rtol);
        }
        printf("a_f: %f, b_f: %f, c_f: %f, c_i2f: %f\n", a_f, b_f, c_f, c_i2f);
    }
}

void test_div(void) {
    float a_f = 0.0;
    float b_f = 0.0;
    int16_t a_i = 0;
    int16_t b_i = 0;
    printf("---[ test_div ]---\n");
    for (int i=0; i<10; i++) {
        a_f = 2.0f*(float)rand() / (float)RAND_MAX - 1.0f;
        b_f = 2.0f*(float)rand() / (float)RAND_MAX - 1.0f;
        float2fixed(a_f, &a_i);
        float2fixed(b_f, &b_i);
        const int16_t c_i = divfp(a_i, b_i);
        const float c_f = a_f / b_f;
        float c_i2f = 0.0f;
        fixed2float(c_i, &c_i2f, FRAC);
        const float err = fabs(c_f - c_i2f);
        const float rtol = fabs(c_f * RTOL);
        if (err < rtol) {
            printf("[PASSED] err: %f, %f, ", err, rtol);
        } else {
            printf("[FAILED] err: %f, %f, ", err, rtol);
        }
        printf("a_f: %f, b_f: %f, c_f: %f, c_i2f: %f\n", a_f, b_f, c_f, c_i2f);
    }
}

int main(int argc, char **argv) {
    test_mul();
    test_div();
    return 0;
}

