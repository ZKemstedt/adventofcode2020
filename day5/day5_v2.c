#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

char *replace_char(char* str, char find, char replace){
    char *pos = strchr(str, find);
    while (pos) {
        *pos = replace;
        pos = strchr(pos, find);
    }
    return str;
}

int main() {
    FILE *stream;
    size_t len = 0;
    ssize_t nread;
    char *line = NULL;
    int min = 1024;
    int max = 0;
    int sum = 0;
    int id;
    int seat;
    
    stream = fopen(INPUT_FILE, "rb");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&line, &len, stream)) != -1) {
        line[nread] = '\0';
        line = replace_char(line, 'R', '1');
        line = replace_char(line, 'B', '1');
        line = replace_char(line, 'L', '0');
        line = replace_char(line, 'F', '0');

        id = (int) strtol(line, NULL, 2);
        sum += id;
        min = id < min ? id : min;
        max = id > max ? id : max;
    }

    seat = ((max - min + 1) / 2.0 * (min + max)) - sum;

    printf("Day 5 - Part 1: %d\n", max);
    printf("Day 5 - Part 2: %d\n", seat);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}