#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    float a; // alpha
    float b; // beta
    float c; // gamma
} rot3;


const float K1 = 40.0;
const float inc = 0.6;
const float cube_size = 20.0;
const int width = 160;
const int height = 44;
const int distance = 100;
const int char_width = 2;
const int char_height = 1;
int idx = 0;
char *buffer;
float *z_buffer;
const int background = ' ';

float calc_x(vec3 v, rot3 r) {
    return v.x * (cosf(r.a) * cosf(r.b)) +
           v.y * (cosf(r.a) * sinf(r.b) * sinf(r.c) - sinf(r.a) * cosf(r.c)) +
           v.z * (sinf(r.a) * sinf(r.c) + cosf(r.a) * sinf(r.b) * cosf(r.c));
}

float calc_y(vec3 v, rot3 r) {
    return v.x * (sinf(r.a) * cosf(r.b)) +
           v.y * (cosf(r.a) * cosf(r.c) + sinf(r.a) * sinf(r.b) * sinf(r.c)) +
           v.z * (sinf(r.a) * sinf(r.b) * cosf(r.c) - cosf(r.a) * sinf(r.c));
}

float calc_z(vec3 v, rot3 r) {
    return v.x * (-sinf(r.b)) + 
           v.y * (cosf(r.b) * sinf(r.c)) +
           v.z * (cosf(r.b) * cosf(r.c));
}

void calculate_for_surface(vec3 point, rot3 rot, char ch) {
    const float x = calc_x(point, rot);
    const float y = calc_y(point, rot);
    const float z = calc_z(point, rot) + distance;
    const float ooz = 1.0 / z;
    const int col = (int)roundf(width  / 2.0 + K1 * ooz * x * char_width);
    const int row = (int)roundf(height / 2.0 + K1 * ooz * y * char_height);
    const int k = col + row * width;
    if (k >= 0 && k < width * height) {
        if (ooz > z_buffer[k]) {
            z_buffer[k] = ooz;
            buffer[k] = ch;
        }
    }
}

int main(int argc, char *argv[]) {
    rot3 rot = {.a = 0.0, .b = 0.0, .c = 0.0};
    buffer = (char *)malloc(width * height * sizeof(char));
    z_buffer = (float *)malloc(width * height * sizeof(float));
    printf("\x1b[2J"); // Clear screen
    while (true) {
        memset(buffer, background, width * height * sizeof(char));
        memset(z_buffer, 0, width * height * sizeof(float));
        for (float cube_x = -cube_size; cube_x < cube_size; cube_x += inc) {
            for (float cube_y = -cube_size; cube_y < cube_size; cube_y += inc) {
                calculate_for_surface((vec3){cube_x, cube_y, -cube_size}, rot, '@');
                calculate_for_surface((vec3){cube_x, cube_y,  cube_size}, rot, '#');
                calculate_for_surface((vec3){ cube_size, cube_y, cube_x}, rot, 'X');
                calculate_for_surface((vec3){-cube_size, cube_y, cube_x}, rot, '~');
                calculate_for_surface((vec3){cube_x, -cube_size, cube_y}, rot, ';');
                calculate_for_surface((vec3){cube_x,  cube_size, cube_y}, rot, '+');
            }
        }
        printf("\x1b[H"); // Move cursor to home position
        for (int k = 0; k < width * height; k++) {
            putchar(k % width ? buffer[k] : 10);
        }
        rot.a += 0.004;
        rot.b -= 0.005;
        rot.c += 0.006;
        usleep(500);
    }
    free(buffer);
    free(z_buffer);
    buffer = NULL;
    z_buffer = NULL;
    return 0;
}
