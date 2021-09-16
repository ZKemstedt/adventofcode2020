#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELEN 10
#define ALLSEATS 1024
#define DEBUG 0

#if DEBUG
const char *long_to_binary(long x) {
    static char b[11];
    b[0] = '\0';

    for (int z = 512; z > 0; z >>= 1) {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }
    return b;
}
#endif

int find_max(int *seats) {
    int max = 0;
    for (int i = 0; i < ALLSEATS; i++) {
        if (seats[i]) {
            max = (i > max) ? i : max;
        }
    }
    if (max) {
        printf("The highest seat id was %d\n", max+1);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int find_seat(int *seats) {
    int p = 1;
    while (p < ALLSEATS - 1) {
        if (!seats[p]) {
            if (seats[p+1] && seats[p-1]) {
                printf("I found my seat: %d\n", p+1);
                return EXIT_SUCCESS;
            }
        }
        p++;
    }
    return EXIT_FAILURE;
}

int parse_seats(char *text) {
    int seat, bit;
    int seats[ALLSEATS] = {};

    #if DEBUG
    char buf[LINELEN + 1];
    buf[LINELEN] = '\0';
    #endif

    while (1) {
        if (strcspn(text, "\n") != LINELEN) break;

        #if (DEBUG)
        strncpy(buf, text, LINELEN);
        buf[10] = '\0';
        #endif

        seat = 0;
        for (int i = 9; i >= 0; i--) {
            switch (*text) {
            case 'B':
            case 'R':
                bit = 1;
                break;
            case 'F':
            case 'L':
                bit = 0;
                break;
            default:
                printf("Error: invalid character detected in input steam: %c\n", *text);
                return EXIT_FAILURE;
            }
            text++;
            seat ^= (bit << i); // Flip the corresponding bit
        }
        seats[seat - 1] = 1; // register seat
        text++;

        #if DEBUG
        printf("%s => %s => %d\n", buf, long_to_binary(seat), seat);
        #endif
    }
    return find_max(seats) ^ find_seat(seats);
}

int main() {
    FILE *file;
    long long filesize;
    char *text;

    if (sizeof(int) * 8 < 10) {
        printf("Error: Unsuported platform\n");
        return EXIT_FAILURE;
    }

    file = fopen("input.txt", "rb");
    if (file == NULL) {
        printf("Error: failed to open file\n");
        return EXIT_FAILURE;
    }
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    rewind(file);

    text = malloc(filesize);
    if (text == NULL) {
        fclose(file);
        printf("Error: failed to allocate memory for file contents\n");
        return EXIT_FAILURE;
    }
    fread(text, 1, filesize+1, file);
    fclose(file);
    text[filesize] = '\0';

    int result = parse_seats(text);

    free(text);
    return result;
}
