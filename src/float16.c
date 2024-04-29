#include <stdint.h>
#include <math.h>
#include <stdio.h>

#define BIN_FMT "%c%c%c%c%c%c%c%c"
#define BYTE2BIN(byte)                                                         \
    ((byte)&0x80 ? '1' : '0'), ((byte)&0x40 ? '1' : '0'),                      \
        ((byte)&0x20 ? '1' : '0'), ((byte)&0x10 ? '1' : '0'),                  \
        ((byte)&0x08 ? '1' : '0'), ((byte)&0x04 ? '1' : '0'),                  \
        ((byte)&0x02 ? '1' : '0'), ((byte)&0x01 ? '1' : '0')

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

void f32_to_f16(float *src, _Float16 *dst) {
    float tmp_src = *src;
    _Float16 tmp_dst = (_Float16)tmp_src;
    *dst = tmp_dst;
}

void print_f16(float *val_src, _Float16 *val_dst) {
    uint16_t *val_dst_ptr = (uint16_t *)val_dst;
    printf("val_src f32: % 0.6f, ", *val_src);
    float val_dst_f32 = (float)*val_dst;
    printf("val_dst f16: % 0.6f, ", val_dst_f32);
    printf("val_dst dec: % 5d, ", *val_dst_ptr);
    printf("val_dst hex: 0x%x, ", *val_dst_ptr);
    printf("val_dst bin: " BIN_FMT " " BIN_FMT "\n",
           BYTE2BIN(*val_dst_ptr >> 8), BYTE2BIN(*val_dst_ptr));
}

int main(int argc, char *argv[]) {

    // src value
    float val_src;
    // dst value placeholder
    _Float16 val_dst;

    /* for (int i = 0; i < 18; i++) { */
    /*     // src value */
    /*     val_src = 1.4142*pow(2.0, (float)i); */
    /*     // dst value placeholder */
    /*     f32_to_f16(&val_src, &val_dst); */
    /*     print_f16(&val_src, &val_dst); */
    /* } */
    val_src = -0.5;
    f32_to_f16(&val_src, &val_dst);
    print_f16(&val_src, &val_dst);
    val_src = -.63118842747981;
    f32_to_f16(&val_src, &val_dst);
    print_f16(&val_src, &val_dst);
    val_src = 2;
    f32_to_f16(&val_src, &val_dst);
    print_f16(&val_src, &val_dst);
    val_src = 16;
    f32_to_f16(&val_src, &val_dst);
    print_f16(&val_src, &val_dst);


    return 0;
}
