#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_bytes(char *ty, char *val, unsigned char *bytes, size_t num_bytes) {
    printf("(%*s) %*s = [ ", 15, ty, 16, val);
    for (size_t i = 0; i < num_bytes; i++) {
        // printf("%*u ", 3, bytes[i]);
        printf("%*x ", 3, bytes[i]);
    }
    printf("]\n");
}

#define SHOW(T, V)                                                             \
    do {                                                                       \
        T x = V;                                                               \
        print_bytes(#T, #V, (unsigned char *)&x, sizeof(x));                   \
    } while (0)

int main(int argc, char *argv[]) {
    char *s1 = "1234567890";
    printf("%s\n", s1);
    printf("strlen s1: %lu\n", strlen(s1));

    for (int i = 0; i < strlen(s1) + 1; i++) {
        SHOW(char, *(s1 + i));
    }

    return EXIT_SUCCESS;
}
