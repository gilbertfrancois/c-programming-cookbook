/* Pointer demo */
#include <stdio.h>

int main(int argc, char *argv[]) {

    int a = 1;
    int *b = &a;

    /* show value */
    printf(" a: %d\n", a);
    /* show pointer address of a */
    printf("&a: %p\n", (void *)&a);
    /* show value of b (= pointer address of a) */
    printf(" b: %p\n", (void *)b);
    /* show value pointed by b */
    printf("*b: %d\n", *b);
    /* show pointer address of b */
    printf("&b: %p\n", (void *)&b);

    return 0;
}
