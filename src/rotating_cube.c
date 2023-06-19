#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

float A = 0.0;
float B = 0.0;
float C = 0.0;
const float K1 = 40.0;
const float inc = 0.6;
const float cube_size = 20.0;
const int width = 160;
const int height = 44;
const int distance = 100;
int idx = 0;
char *buffer;
float *z_buffer;
const int background = ' ';

float calculate_x(float i, float j, float k) {
    return j * sinf(A) * sinf(B) * cosf(C) - k * cosf(A) * sinf(B) * cosf(C) +
           j * cosf(A) * sinf(C) + k * sinf(A) * sinf(C) +
           i * cosf(B) * cosf(C);
}

float calculate_y(float i, float j, float k) {
    return j * cosf(A) * cosf(C) + k * sinf(A) * cosf(C) -
           j * sinf(A) * sinf(B) * sinf(C) + k * cosf(A) * sinf(B) * sinf(C) -
           i * cosf(B) * sinf(C);
}

float calculate_z(float i, float j, float k) {
    return k * cosf(A) * cosf(B) - j * sinf(A) * cosf(B) + i * sinf(B);
}

void calculate_for_surface(float cube_x, float cube_y, float cube_z, char ch) {
    const float x = calculate_x(cube_x, cube_y, cube_z);
    const float y = calculate_y(cube_x, cube_y, cube_z);
    const float z = calculate_z(cube_x, cube_y, cube_z) + distance;
    const float ooz = 1.0 / z;
    const int col = (int)round(width / 2.0 + K1 * ooz * x * 2);
    const int row = (int)round(height / 2.0 + K1 * ooz * y);
    const int k = col + row * width;
    if (k >= 0 && k < width * height) {
        if (ooz > z_buffer[k]) {
            z_buffer[k] = ooz;
            buffer[k] = ch;
        }
    }
}

int main(int argc, char *argv[]) {
    buffer = (char *)malloc(width * height * sizeof(char));
    z_buffer = (float *)malloc(width * height * sizeof(float));
    printf("\x1b[2J"); // Clear screen
    while (true) {
        memset(buffer, background, width * height * sizeof(char));
        memset(z_buffer, 0, width * height * sizeof(float));
        for (float cube_x = -cube_size; cube_x < cube_size; cube_x += inc) {
            for (float cube_y = -cube_size; cube_y < cube_size; cube_y += inc) {
                calculate_for_surface(cube_x, cube_y, -cube_size, '@');
                /* calculate_for_surface(-cube_x, cube_y, cube_size, '#'); */
                /* calculate_for_surface(cube_size, cube_y, cube_x, 'X'); */
                /* calculate_for_surface(-cube_size, cube_y, -cube_x, '~'); */
                /* calculate_for_surface(cube_x, -cube_size, -cube_y, ';'); */
                /* calculate_for_surface(cube_x, cube_size, cube_y, '+'); */
            }
        }
        printf("\x1b[H"); // Move cursor to home position
        for (int k = 0; k < width * height; k++) {
            putchar(k % width ? buffer[k] : 10);
        }
        A += 0.004;
        /* B -= 0.005; */
        /* C += 0.006; */
        usleep(500);
    }
    free(buffer);
    free(z_buffer);
    buffer = NULL;
    z_buffer = NULL;
    return 0;
}
