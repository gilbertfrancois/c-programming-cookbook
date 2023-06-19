#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void message_line(char *message) {
    // Prevent buffer overflow.
    if (strlen(message) > 73) {
        return;
    }
    char line[80] = "";
    strcat(line, "\n---[ ");
    strcat(line, message);
    strcat(line, " ]");
    unsigned long line_len = strlen(line);
    for (int i = 0; i < 79 - line_len; i++) {
        strcat(line, "-");
    }
    printf("%s\n\n", line);
}

