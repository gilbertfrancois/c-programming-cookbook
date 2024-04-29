#include <stdio.h>
#include <stdlib.h>

struct S1 {
    int p1;
    int p2;
};

struct S2 {
    int p1;
    struct S1 s1;
    int p2;
};

int main(int argc, char *argv[]) {
    struct S1 s1 = {1, 2};
    struct S2 s2 = {1, {2, 3}, 4};
    struct S2 *p = &s2;

    p->p1 = 0;

    printf("s1.p1 = %d\n", s1.p1);
    printf("s1.p2 = %d\n", s1.p2);
    printf("s2.p1 = %d\n", s2.p1);
    printf("s2.s1.p1 = %d\n", s2.s1.p1);
    printf("s2.s1.p2 = %d\n", s2.s1.p2);
    printf("s2.p2 = %d\n", s2.p2);

    return EXIT_SUCCESS;
}
