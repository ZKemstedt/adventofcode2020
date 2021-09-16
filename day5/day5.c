#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_seats(char *text) {
    int min = 1024;
    int max = 0;
    int sum = 0;
    int my_seat;
    int seat;
    int bit;

    while (*text) {
        if (strcspn(text, "\n") != 10) break;

        /*
        Parsing input as a binary representation: FBFFFFBRRL => 0100001110 char by char,
        keeping a inverse relation between the char position and the bit position:
            first char = highest bit (i=9) -> last char = lowest bit (i=0)
        */
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
            seat |= (bit << i); // Flip ones
        }
        text++;
        max = seat > max ? seat : max;
        min = seat < min ? seat : min;
        sum += seat;
    }

    my_seat = ((max - min + 1) * 0.5 *  (min + max)) - sum;

    printf("The highest seat id is %d\n", max);
    printf("The lowest seat id is %d\n", min);
    printf("My seat id is %d\n", my_seat);

    return EXIT_SUCCESS;
}

int main() {
    FILE *file;
    long long filesize;
    char *text;

    file = fopen("input.txt", "rb");
    if (file == NULL) {
        printf("Error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    rewind(file);

    text = malloc(filesize);
    if (text == NULL) {
        fclose(file);
        printf("Error: failed to allocate memory for file contents\n");
        exit(EXIT_FAILURE);
    }
    fread(text, 1, filesize+1, file);
    fclose(file);
    text[filesize] = '\0';

    int result = parse_seats(text);

    free(text);
    exit(result);
}
