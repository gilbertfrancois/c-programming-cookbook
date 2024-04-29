/*
 * Print the first 128 ascii characters.
 */
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    uint8_t i, j = 0;
    for (j = 1; j < 8; j++) {
        i = 0;
        printf("%04d | ", j * 32 + i);
        for (i = 0; i < 32; i++) {
            printf("%c ", j * 32 + i);
        }
        printf("\n");
    }
    return 0;
}
