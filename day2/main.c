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
    int valid_counter1 = 0, valid_counter2 = 0;

    // forward slash when not on windows
    file = fopen("day2/input.txt", "rb");
    if (file == NULL) {
        file = fopen("input.txt", "rb");
        if (file == NULL) {
            fputs("File error", stderr);
            return(1);
        }
    }

    while (fgets(line, ROW_BUFFER_SIZE, file)) {
        int pos1, pos2, count;
        char pwd[20];
        char key;

        line[strcspn(line, "\n")] = 0;

        sscanf(line, "%d-%d %c: %s", &pos1, &pos2, &key, pwd);

        count = scountc(pwd, key);
        if (count >= pos1 && count <= pos2) {
            valid_counter1++;
        }

        if (check_pos(pwd, key, pos1-1) != check_pos(pwd, key, pos2-1)) {
            valid_counter2++;
        }
    }

    fclose(file);

    printf("Solution for part1: %d\n", valid_counter1);
    printf("Solution for part2: %d\n", valid_counter2);
    return 0;
}


// returns 1 on success and 0 on failure
int set_buffer(char **buf, int size) {
    free(*buf);
    *buf = (char *) calloc(size, sizeof(char));
    if (*buf == NULL) {
        return 0;
    }
    return 1;
}

// accessing the other args by reference is probably faster?
void validate(int charcount, int *valid_count1, int *valid_count2, int pos1, int pos2, char key, char *pwd) {
    if ( (pwd[pos1-1] == key) != (pwd[pos2-1] == key) ) {
        (*valid_count2)++;
    }
    if (charcount >= pos1 && charcount <= pos2)
        (*valid_count1)++;
}


/* Read the whole file into memory as one large
string and then iterate over it one char at a time
 */
int single_iteration() {
    long filesize;
    FILE *file;
    char *text;
    
    // file = fopen("day2\\input.txt", "rb");    // open
    // forward slash when not on windows
    file = fopen("day2/input.txt", "rb");
    if (file == NULL) {
        file = fopen("input.txt", "rb");
        if (file == NULL) {
            fputs("File error", stderr);
            return 1;
        }
    }

    fseek(file, 0, SEEK_END);   // get size
    filesize = ftell(file);
    rewind(file);
    
    text = malloc(filesize + 1);    // allocate
    if (text == NULL) {
        fclose(file);
        goto merror;
    }
    fread(text, 1, filesize, file);   // read
    fclose(file);
    text[filesize] = '\0';   // terminate


    char *c = text, *tmp;
    char key;
    int state = 0,
        advance = 0,
        i = 0,
        valid_counter1 = 0,
        valid_counter2 = 0,
        valid1_char_counter = 0,
        pos1,
        pos2;
    
    tmp = (char *) calloc(20, sizeof(char));
    if (tmp == NULL)
        goto merror;

    do {
        switch (*c) {
            case '-':                       /* done with state 0 */
                pos1 = atoi(tmp);
                advance++;
                break;
            case ' ':
                if (state == 1) {           /* done with state 1 */
                    pos2 = atoi(tmp);
                    advance++;
                } else if (state == 2) {    /* done with state 2 */
                    key = tmp[0];
                    advance++;
                }
                break;
            case ':':   /* ignore */
                break;
            case '\n':  /* done with line */
                advance++;
                break;
            default:    /* add to buffer */
                tmp[i] = *c;
                i++;
                if (state == 3) { // char counter to validate part1
                    if (*c == key)
                        valid1_char_counter++;
                }
                break;
        }

        if (advance) {
            i = 0;
            advance--;
            state++;
            if (state == 4) { // validate and reset state
                validate(valid1_char_counter, &valid_counter1, &valid_counter2, pos1, pos2, key, tmp);
                valid1_char_counter = 0;
                state = 0;
            }
            if (!set_buffer(&tmp, 20))
                goto merror;
        }
    } while (*(c++));

    printf("Solution for part1: %d\n", valid_counter1);
    printf("Solution for part2: %d\n", valid_counter2);

    return 0;

    // cleanup for memory errors
    merror:
        fputs("Memory allocation error", stderr);
        if (text != NULL)
            free(text);
        if (tmp != NULL)
            free(tmp);
        return 1;
}

int main(int argc, char *argv[]) {
    int run1 = 1, run2 = 1;
    
    if (argc > 1)
        run1 = atoi(argv[1]);
    if (argc > 2)
        run2 = atoi(argv[2]);

    // normal operation
    if (run1)
        if (run())
            return EXIT_FAILURE;

    // as a single iteraion
    if (run2)
        if (single_iteration())
            return EXIT_FAILURE;

    return EXIT_SUCCESS;        
}