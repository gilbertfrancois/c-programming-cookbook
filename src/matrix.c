#include <math.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

const int width = 80;
const int height = 24;
const int n_permutations = 12;
const int p_rain = 8;

int *drop_col;
int *drop_speed;
int *drop_speed_counter;
int *drop_start;
int *drop_length;
char *nametable_buffer;

int rnd(int max) {
    return (int)(0.5f + (float)max * rand() / (float)RAND_MAX);
}
 
char get_char(void) {
    char c = (char) rnd(94);
    c = c + 32;
    return c;
}

void update_rnd_char(void) {
    int k = width * height;
    for (int i=0; i < n_permutations; i++) {
        int j = rnd(k);
        if (nametable_buffer[j] != 0x20) {
            char c = get_char();
            nametable_buffer[j] = c;
        }
    }
}

void update_rain_state(void) {
    int col = rnd(p_rain*width);
    if (col < width) {
    int is_raining = drop_col[col];
        if (is_raining == 0) {
            drop_col[col] = 1;
            drop_speed[col] = rnd(7) + 1;
            drop_speed_counter[col] = 0;
            drop_start[col] = 0;
            drop_length[col] = height / 2 + rnd(height / 2);
        }
    }
}

void update_rain_column(int col) {
    int start = drop_start[col];
    int length = drop_length[col];
    int end = start - length;
    if (end > height) {
        drop_col[col] = 0;
        drop_speed[col] = 0;
        drop_speed_counter[col] = 0;
        drop_start[col] = 0;
        return;
    }
    if (end < 0) {
        end = 0;
    }
    if (start < height) {
        const unsigned long k = start * width + col;
        char c = get_char();
        nametable_buffer[k] = c;
    }
    if (end > 0) {
        const unsigned long k = (end - 1) * width + col;
        nametable_buffer[k] = 0x20;
    }
    drop_start[col]++;
}

void init(void) {
    for (int row=0; row < height; row++) {
        for (int col=0; col < width; col++) {
            int k = col + row * width;
            nametable_buffer[k] = 0x20;
        }
    }
    for (int i = 0; i < width; i++) {
        drop_col[i] = 0;
        drop_speed[i] = 0;
        drop_speed_counter[i] = 0;
        drop_start[i] = 0;
        drop_length[i] = 0;
    }
}

void update_rain_columns(void) {
    for (int i = 0; i < width; i++) {
        if (drop_col[i] == 1) {
            if (drop_speed_counter[i] < drop_speed[i]) {
                drop_speed_counter[i]++;
            } else {
                drop_speed_counter[i] = 0;
                update_rain_column(i);
            }
        }
    }
}

void update_screen(void) {
    /* printf("\x1b[2J"); // Clear screen */
    printf("\x1b[H"); // Move cursor to home position
    for (int row=0; row < height; row++) {
        for (int col=0; col < width; col++) {
            putchar(nametable_buffer[row * width + col]);
        }
        putchar(10);
    }
}


void mainloop(void) {
    update_rain_state();
    update_rain_columns();
    update_rnd_char();
    update_screen();
}

int main(int argc, char* argv[]) {

    drop_col = (int*)malloc(width * sizeof(int));
    drop_speed = (int*)malloc(width * sizeof(int));
    drop_speed_counter = (int*)malloc(width * sizeof(int));
    drop_start = (int*)malloc(width * sizeof(int));
    drop_length = (int*)malloc(width * sizeof(int));
    nametable_buffer = (char*)malloc(width * height * sizeof(char));

    init();

    while (true) {
        mainloop();
        usleep(7500);
    }

    free(nametable_buffer);
    free(drop_col);
    free(drop_speed);
    free(drop_speed_counter);
    free(drop_start);
    free(drop_length); 
    exit(EXIT_SUCCESS);
}

