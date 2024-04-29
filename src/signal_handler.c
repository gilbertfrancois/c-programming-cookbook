#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler_interrupt(int val) {
    printf(" -> %d received\n", val);
    exit(0);
}

void handler_quit(int val) {
    printf(" -> %d received\n", val);
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handler_interrupt);
    signal(SIGQUIT, handler_quit);
    while (1)
        ;
    return EXIT_SUCCESS;
}
