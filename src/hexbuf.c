#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char STX = 0x02;
const char ETX = 0x03;
const char ACK = 0x06;
const char LF = 0x10;
const char CR = 0x13;
const char XOFF = 0;
const char XON = 0;
const unsigned long MAX_LEN_PAYLOAD = 45;
const unsigned int BINARY_BITS = 16;

// Convert integer number to binary representation.
// The buffer must have bits bytes length.
void int2bin(int number, char *buffer, unsigned int bits) {
    memset(buffer, 0, bits + 1);
    buffer += bits - 1;
    for (int i = bits - 1; i >= 0; i--) {
        *buffer-- = (number & 1) + '0';
        number >>= 1;
    }
}

int calc_LRC(char *data, bool with_debug) {
    char binstr[17];
    int lrc = 0;
    for (int i = 0; i < strnlen(data, 64); i++) {
        if (with_debug) {
            int2bin(lrc, binstr, BINARY_BITS);
            printf("%s XOR ", binstr);
            int2bin(data[i], binstr, BINARY_BITS);
            printf("%s -> ", binstr);
        }
        lrc ^= data[i];
        if (with_debug) {
            int2bin(lrc, binstr, BINARY_BITS);
            printf("%s\n", binstr);
        }
    }
    return lrc;
}

void make_message(char *payload, char *buffer) {
    int cursor = 0;
    if (strlen(payload) > MAX_LEN_PAYLOAD) {
        printf("Payload exceeds buffer length.\n");
        exit(1);
    }
    printf("strlen buffer : %lu\n", strlen(buffer));
    printf("strlen payload: %lu\n", strlen(payload));
    buffer[cursor] = STX;
    strcpy(buffer + 1, payload);
    cursor = strlen(buffer);
    buffer[cursor++] = ETX;
    const int LRC = calc_LRC(buffer, true);
    buffer[cursor++] = LRC;
    buffer[cursor++] = 0x00;
    printf("strlen buffer : %lu\n", strlen(buffer));
    printf("strlen payload: %lu\n", strlen(payload));
}

void print_hex(char *buffer) {
    for (int i = 0; i < strlen(buffer); i++) {
        printf("0x%x ", buffer[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    char *buffer = (char *)malloc((MAX_LEN_PAYLOAD + 3) * sizeof(char));
    memset(buffer, 0, MAX_LEN_PAYLOAD + 3);
    char *payload = (char *)malloc(MAX_LEN_PAYLOAD * sizeof(char));
    memset(payload, 0, MAX_LEN_PAYLOAD);
    char *entity_id = "801BF7B1124A04";
    strcpy(payload, entity_id);
    make_message(payload, buffer);
    printf("entity_id: %s\n", payload);
    print_hex(buffer);
    free(payload);
    free(buffer);
    return 0;
}
