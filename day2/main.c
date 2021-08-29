#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ROW_BUFFER_SIZE 32

int scountc(char *string, char key) {
    int i;
    char *s = string;
    for (i = 0; s[i]; s[i]==key ? i++ : *s++);
    return i;
}

int check_pos(char *string, char key, int pos) {
    if (strspn(string, "\0") >= key)
        return 0;
    return string[pos] == key;
}

int run() {
    FILE *file;
    char line[ROW_BUFFER_SIZE];
    int valid1 = 0, valid2 = 0;

    file = fopen("day2\\input.txt", "rb");
    if (file == NULL) {
        fputs("File error", stderr);
        return 1;
    }

    while (fgets(line, ROW_BUFFER_SIZE, file)) {
        int pos1, pos2, count;
        char pwd[20];
        char key;

        line[strcspn(line, "\n")] = 0;

        sscanf(line, "%d-%d %c: %s", &pos1, &pos2, &key, pwd);

        count = scountc(pwd, key);
        if (count >= pos1 && count <= pos2) {
            valid1++;
        }

        if (check_pos(pwd, key, pos1-1) != check_pos(pwd, key, pos2-1)) {
            valid2++;
        }
    }

    fclose(file);

    printf("Solution for part1: %d\n", valid1);
    printf("Solution for part2: %d\n", valid2);
    return 0;
}

void advance(int *state, int* i) {
    i = 0;
    state++;
    if (state == 4)
        state = 0;
}

void validate(int *valid_counter, int pos1, int pos2, char key, char *pwd) {

}


/* Read the whole file into memory as one large
string and then iterate over it one char at a time
 */
int single_iteration() {
    long filesize;
    FILE *file;
    char *text;
    
    file = fopen("day2\\input.txt", "rb");    // open
    if (file == NULL) {
        fputs("File error", stderr);
        return(1);
    }
    fseek(file, 0, SEEK_END);   // get size
    filesize = ftell(file);
    rewind(file);
    
    text = malloc(filesize + 1);    // allocate
    if (text == NULL) {
        fputs("Memory allocation error", stderr);
        fclose(file);
        return(1);
    }
    fread(text, 1, filesize, file);   // read
    fclose(file);
    text[filesize] = 0;   // terminate
    assert(text[0]);

    char pwd[20];
    char *c = text, *tmp;
    char key;
    int state = 0, i = 0, valid1 = 0, valid2 = 0, pos1, pos2;
    do {
        switch (*c)
            {
            case '-':   /* done with state 0 */
                assert(state == 0);
                printf("%s-", tmp);
                // tmp[i] = 0;
                pos1 = atoi(tmp);
                advance(&state, &i);
                break;
            case ' ':   /* done with state 1 or done with state 2 */
                assert(state == 1 || state == 2);
                if (state == 1) {
                    // tmp[i] = 0;
                    pos2 = atoi(tmp);
                    advance(&state, &i);
                    break;
                }
                if (state == 2) {
                    assert(tmp[0]);
                    assert(i == 1);
                    key = tmp[0];
                    advance(&state, &i);
                    break;
                }
            case ':':   /* ignore */
                break;
            case '\n':  /* done with line, validate pwd and then reset state */
                assert(state == 3);
                // pwd[i] = 0;
                validate(&valid2, pos1, pos2, key, pwd);
                advance(&state, &i);
                break;
            default:
                assert(state < 4);
                assert(i < 21);
                tmp[i] = c[*c+i];
                i++;
                break;
            }
    } while (*(c++));

    return 0;
}

int main() {
    // normal operation
    if (run())
        exit(1);



    if (single_iteration())
        exit(1);

    return 0;        
}