#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define arraylen 1000

typedef unsigned long long INT;

struct range {
    INT *start;
    INT *end;
};

void printNums(INT *start, INT *end);
INT min(INT *start, INT *end);
INT max(INT *start, INT *end);
INT *loadNumbers();
INT findInvalidValue(INT *start, INT *end, int preambleSize);
bool isValid(INT *start, INT *end, INT value);
bool isIn(INT *start, INT *end, INT value);
struct range *findWeakness(INT *start, INT *end, INT value);
struct range *numbersThatStartsSumTo(INT target, INT *start, INT *end);

int main()
{
    INT *numbers = loadNumbers();

    INT invalidValue = findInvalidValue(numbers, numbers + arraylen, 25);
    printf("Part 1: %llu\n", invalidValue);

    // -> start, count
    struct range *weakness = findWeakness(numbers, numbers + arraylen, invalidValue);

    printNums(weakness->start, weakness->end);
    INT a = min(weakness->start, weakness->end);
    INT b = max(weakness->start, weakness->end);

    printf("Part 2min: %llu\n", a);
    printf("Part 2max: %llu\n", b);
    printf("Part 2: %llu\n", a + b);
    // 3535124
    
    free(numbers);
    free(weakness);
}

void printNums(INT *start, INT *end) {
    for (INT *c = start + 1; c < end; c++) {
        printf("%llu\n", *c);
    }
}

INT max(INT *start, INT *end) {
    INT val = *start;
    for (INT *c = start + 1; c < end; c++) {
        if (*c > val) {
            val = *c;
        }
    }
    return val;
}

INT min(INT *start, INT *end)
{   
    INT m = *start;
    do {
        m = m > *end ? *end : m;
        end--;
    }
    while (start < end);
    return m;
}

INT findInvalidValue(INT *start, INT *end, int preambleSize)
{
    INT *preambleStart = start;
    INT *preambleEnd = start + preambleSize - 1;
    INT *current = start + preambleSize;

    while (isValid(preambleStart, preambleEnd, *current)) {
        preambleStart++;
        preambleEnd++;
        current++;
    }

    return *current;
}

bool isValid(INT *start, INT *end, INT value)
{
    for (INT *c = start; c <= end; c++) {
        if (*c + *c != value && isIn(start, end, value - *c))
            return true;
    }
    return false;
}

bool isIn(INT *start, INT *end, INT value)
{
    for (INT *i = start; i <= end; i++) {
        if (*i == value) return true;
    }
    return false;
}


struct range *findWeakness(INT *start, INT *end, INT value)
{
    do {
        struct range *found = numbersThatStartsSumTo(value, start, end);

        if (found != NULL) return found;

        start++;
    } while (start < end);

    printf("FAILURE!!");
    exit(1);
    return NULL;
}

struct range *numbersThatStartsSumTo(INT target, INT *start, INT *end)
{
    INT sum = 0;
    for (INT *c = start; c <= end; c++) {
        sum += *c;
        if (sum == target) {

            struct range *res = malloc(sizeof(struct range));
            assert(res != NULL);
            res->end = c;
            res->start = start;
            return res; 
        }
        if (sum > target) return NULL; // too large
    }
    printf("we failed\n");
    exit(1);
    return NULL;
}

    // for (INT *c = start; c++ <= end && sum < target; sum+=*c)
    
    //struct range result = {.start = xxx, .end = stsadf};
    
    //return result


INT *loadNumbers() {
    FILE *file = fopen("input.txt", "rb");
    if (file == NULL) {
        printf("File does not exist");
        exit(1);
    }

    char *line = NULL;
    int counter = 0;
    size_t len = 0;
    ssize_t nread = 0;

    INT *numbers = malloc(arraylen * sizeof(INT));
    assert(numbers != NULL);

    while ((nread = getline(&line, &len, file)) != -1) {
        numbers[counter++] = strtoull(line, NULL, 10);
    }
    return numbers;
}
