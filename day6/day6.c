#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"

/* Set all fields of an array arr to the value v */
void array_set(int arr[26], int v) {
    for (int i = 0; i < 26; i++) {
        arr[i] = v;
    }
}

void array_print(int arr[26]) {
    char start = 'a';
    char empty = '_';
    for (int i = 0; i < 26; i++) {
        printf("%d", arr[i]);
        
    }
    printf(" --- ");
    for (int i = 0; i < 26; i++) {
        printf("%c", arr[i] ? start + i : empty);
    }
    printf("\n");
}

/* increment the counter sum for each non-zero value in ans */
void sum_inc(unsigned long long *sum, int ans[26]) {
    for (int i = 0; i < 26; i++) {
        *sum += ans[i];
    }
}

void run(FILE *stream) {
    char *line = NULL, *c = NULL;
    size_t len = 0;
    ssize_t nread = 0;
    unsigned long long sum1 = 0, sum2 = 0;
    /* Groups answers are represented in binary form */
    int answers[26], group1[26], group2[26]; 

    array_set(group1, 0);
    array_set(group2, 1);

    while ((nread = getline(&line, &len, stream)) != -1) {
        if (line[0] == '\n') {
            printf("summarizing...\n");
            sum_inc(&sum1, group1);
            sum_inc(&sum2, group2);
            array_set(group1, 0);
            array_set(group2, 1);
            continue;
        } else if (line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }
        c = line;
        array_set(answers, 0);
        // registering answers
        for (int i = 0; i++ < nread; c++) {
            answers[*c - 'a'] |= 1;
        }
        for (int i = 0; i < 26; i++) {
            group1[i] |= answers[i];
            group2[i] &= answers[i];
        }
        printf("---\n");
        array_print(group1);
        array_print(group2);
    }
    // no newline at end of file, have to sum last count outside of loop
    sum_inc(&sum1, group1);
    sum_inc(&sum2, group2);

    printf("Part 1 sum: %llu\n", sum1);
    printf("Part 2 sum: %llu\n", sum2);

    free(line);
}

int main(int argc, char *argv[])
{
    FILE *stream; 

    stream = fopen(INPUT_FILE, "rb");
    if (stream == NULL) {
        printf("Error: unable to open file\n");
        return (1);
    }
    run(stream);
    fclose(stream);

    return 0;
}

