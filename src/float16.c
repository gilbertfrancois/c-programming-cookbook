#include <stdint.h>
#include <stdio.h>


/* void bin2f16(uint16_t bin, _Float16 *f16) { */
/*     uint16_t sign = (bin & 0x8000) >> 15; */
/*     uint16_t exp = (bin & 0x7C00) >> 10; */
/*     uint16_t frac = (bin & 0x03FF); */
/*     if (exp == 0x1F) { */
/*         if (frac == 0) { */
/*             *f16 = sign ? -INFINITY : INFINITY; */
/*         } else { */
/*             *f16 = NAN; */
/*         } */
/*     } else if (exp == 0) { */
/*         *f16 = sign ? -0.0 : 0.0; */
/*     } else { */
/*         exp -= 15; */
/*         *f16 = (1 + frac / 1024.0) * (1 << exp); */
/*         if (sign) { */
/*             *f16 = -*f16; */
/*         } */
/*     } */
/* } */

/* void f162bin(_Float16 f16, uint16_t *bin) { */
/*     uint16_t sign = (f16 < 0) ? 1 : 0; */
/*     uint16_t exp = 0; */
/*     uint16_t frac = 0; */
/*     if (f16 == 0) { */
/*         *bin = 0; */
/*     } else if (f16 == INFINITY) { */
/*         *bin = 0x7C00; */
/*     } else if (f16 == -INFINITY) { */
/*         *bin = 0xFC00; */
/*     } else if (f16 != f16) { */
/*         *bin = 0x7E00; */
/*     } else { */
/*         if (sign) { */
/*             f16 = -f16; */
/*         } */
/*         int i = 0; */
/*         while (f16 >= 2) { */
/*             f16 /= 2; */
/*             exp++; */
/*         } */
/*         while (f16 < 1) { */
/*             f16 *= 2; */
/*             exp--; */
/*         } */
/*         frac = (f16 - 1) * 1024; */
/*         exp += 15; */
/*         *bin = (sign << 15) | (exp << 10) | frac; */
/*     } */
/* } */

int main(int argc, char *argv[]) {
    uint16_t ipi = 0x4248;
    /* int16_t ipi = 0x4248; */

    _Float16 *fpi = (_Float16 *)&ipi;
    float b = (float)(*fpi);
    printf("%d\n", ipi);
    printf("%p\n", (void *)&ipi);
    printf("%p\n", (void *)fpi);
    printf("%f\n", b);
    return 0;
}
