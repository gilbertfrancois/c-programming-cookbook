#include <stdio.h>

int main() {
    const unsigned long int a1 = sizeof(short int);
    const unsigned long int a2 = sizeof(int);
    const unsigned long int a3 = sizeof(long int);
    const unsigned long int a4 = sizeof(long long int);
    const unsigned long int a5 = sizeof(float);
    const unsigned long int a6 = sizeof(double);
    const unsigned long int a7 = sizeof(long double);

    printf("---[ sizeof(type) ]-----------------\n");
    printf("%20s: %lu byte, %lu bit\n", "short int", a1, a1 * 8);
    printf("%20s: %lu byte, %lu bit\n", "int", a2, a2 * 8);
    printf("%20s: %lu byte, %lu bit\n", "long int", a3, a3 * 8);
    printf("%20s: %lu byte, %lu bit\n", "long long int", a4, a4 * 8);
    printf("%20s: %lu byte, %lu bit\n", "float", a5, a5 * 8);
    printf("%20s: %lu byte, %lu bit\n", "double", a6, a6 * 8);
    printf("%20s: %lu byte, %lu bit\n", "long double", a7, a7 * 8);

    const short int     v1 = 1;
    const int           v2 = 1;
    const long int      v3 = 1;
    const long long int v4 = 1;
    const float         v5 = 0.1;
    const double        v6 = 0.1;
    const long double   v7 = 0.1;
    
    printf("---[ sizeof(variable) ]-------------\n");
    printf("%20s: %lu byte, %lu bit\n", "short int", sizeof(v1), sizeof(v1)*8);
    printf("%20s: %lu byte, %lu bit\n", "int", sizeof(v2), sizeof(v2)*8);
    printf("%20s: %lu byte, %lu bit\n", "long int", sizeof(v3), sizeof(v3)*8);
    printf("%20s: %lu byte, %lu bit\n", "long long int", sizeof(v4), sizeof(v4)*8);
    printf("%20s: %lu byte, %lu bit\n", "float", sizeof(v5), sizeof(v5)*8);
    printf("%20s: %lu byte, %lu bit\n", "double", sizeof(v6), sizeof(v6)*8);
    printf("%20s: %lu byte, %lu bit\n", "long double", sizeof(v7), sizeof(v7)*8);





    return 0;
}
