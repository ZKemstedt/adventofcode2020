#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_BUFFER_SIZE 10 // I had no lines longer than 4 chars
#define MAX_ROW_COUNT 500 // the input file was 200 lines long in my case
#define TARGET 2020

int part1(int numbers[], int rowcount) {
    int i, j;
    for (i = 0; i < rowcount; i++) {
        for (j = 0; j < rowcount; j++) {
            if (numbers[i] + numbers[j] == TARGET) {
                return numbers[i] * numbers[j];
            }
        }
    }
    return 0;
}

int part2(int numbers[], int rowcount) {
    int i, j, k;
    for (i = 0; i < rowcount; i++) {
        for (j = 0; j < rowcount; j++) {
            if (numbers[i] + numbers[j] > TARGET)
                continue;
            for (k = 0; k < rowcount; k++) {
                if (numbers[i] + numbers[j] + numbers[k] == TARGET) {
                    return numbers[i] * numbers[j] * numbers[k];
                }
            }
        }
    }
    return 0;
}


int main() {
    FILE *file;
    char line[ROW_BUFFER_SIZE];
    int numbers[MAX_ROW_COUNT];
    int rowcount = 0, p1, p2;

    file = fopen("day1\\input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        numbers[rowcount] = atoi(line);
        rowcount++;
    }

    fclose(file);

    p1 = part1(numbers, rowcount);
    if (p1)
        printf("Solution for part1: %d\n", p1);
    
    p2 = part2(numbers, rowcount);
    if (p2)
        printf("Solution for part2: %d\n", p2);

    return 0;
}