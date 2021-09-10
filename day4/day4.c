#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "day4.h"

struct Passport {
    char *pid;        // passport id
    char *hcl;        // hair color
    char *byr;        // birth year
    char *iyr;        // issure year
    char *eyr;        // expiration year
    char *cid;        // country id
    char *hgt;        // height
    char *ecl;        // eye color
};

struct Passport *Passport_create() {
    struct Passport *pp = calloc(1, sizeof(struct Passport));
    assert(pp != NULL);
    return pp;
}

void Passport_destroy(struct Passport *pp) {
    assert(pp != NULL);
    if (pp->pid != NULL) free(pp->pid);
    if (pp->hcl != NULL) free(pp->hcl);
    if (pp->byr != NULL) free(pp->byr);
    if (pp->iyr != NULL) free(pp->iyr);
    if (pp->eyr != NULL) free(pp->eyr);
    if (pp->cid != NULL) free(pp->cid);
    if (pp->hgt != NULL) free(pp->hgt);
    if (pp->ecl != NULL) free(pp->ecl);
    free(pp);
}

/* C cannot use strings in switches, so they are hashed first */
void Passport_write_field(struct Passport *pp, char *key, char *val) {
    switch (hash((unsigned char *) key)) {
    case 193502530: pp->pid = strdup(val); break;
    case 193487826: pp->byr = strdup(val); break;
    case 193495449: pp->iyr = strdup(val); break;
    case 193491093: pp->eyr = strdup(val); break;
    case 193488373: pp->cid = strdup(val); break;
    case 193490361: pp->ecl = strdup(val); break;
    case 193493628: pp->hcl = strdup(val); break;
    case 193493768: pp->hgt = strdup(val); break;
    default:
        break;
    }
}

/* Part 1: A passport is valid if all fields (ignoring cid) are set */
int Passport_is_valid(struct Passport *pp) {
    if (!(pp->hcl == NULL) && !(pp->byr == NULL) && !(pp->iyr == NULL) && !(pp->pid == NULL)
        && !(pp->eyr == NULL) && !(pp->hgt == NULL) && !(pp->ecl == NULL))
    {
        // printf("valid :)\n");
        return 1;
    } else {
        // printf("invalid :/\n");
        return 0;
    }
}

/* Part 2: Additional restrictions are applied:
    All fields (ignoring cid) must be set.
    byr - four digits; at least 1920 and at most 2002.
    iyr - four digits; at least 2010 and at most 2020.
    eyr - four digits; at least 2020 and at most 2030.
    hgt - a number followed by either cm or in:
        If cm, the number must be at least 150 and at most 193.
        If in, the number must be at least 59 and at most 76.
    hcl - a # followed by exactly six characters 0-9 or a-f.
    ecl - exactly one of: amb blu brn gry grn hzl oth.
    pid - a nine-digit number, including leading zeroes. */
int Passport_is_valid2(struct Passport *pp) {
    int valid = Passport_is_valid(pp);
    if (valid) {
        valid &= Passport_verify_pid(pp);
        valid &= Passport_verify_byr(pp);
        valid &= Passport_verify_iyr(pp);
        valid &= Passport_verify_eyr(pp);
        valid &= Passport_verify_cid(pp);
        valid &= Passport_verify_hcl(pp);
        valid &= Passport_verify_ecl(pp);
        valid &= Passport_verify_hgt(pp);
    }
    return valid;
}

/* pid (Passport ID) - a nine-digit number, including leading zeroes. */
int Passport_verify_pid(struct Passport *pp) {
    if (strlen(pp->pid) != 9) {
        printf("invalid pid %s (len %lu)\n", pp->pid, strlen(pp->pid));
        return 0;
    }
    char *tmp = pp->pid;
    for (int i=0 ; i<9 ; i++) {
        if (!isdigit(*(tmp++))) {
            printf("invalid pid %s (not a digit: %c)\n", pp->pid, *(--tmp));
            return 0;
        }
    }
    return 1;
}

/* byr (Birth Year) - four digits; at least 1920 and at most 2002. */
int Passport_verify_byr(struct Passport *pp) {
    long tmp = strtol(pp->byr, NULL, 10);
    if (2003 > tmp && tmp > 1919) {
        return 1;
    } else {
        printf("invalid birth year %s\n", pp->byr);
        return 0;
    }
}

/* iyr (Issue Year) - four digits; at least 2010 and at most 2020. */
int Passport_verify_iyr(struct Passport *pp) {
    long tmp = strtol(pp->iyr, NULL, 10);
    if (2021 > tmp && tmp > 2009) {
        return 1;
    } else {
        printf("invalid issue year %s\n", pp->iyr);
        return 0;
    }
}

/* eyr (Expiration Year) - four digits; at least 2020 and at most 2030. */
int Passport_verify_eyr(struct Passport *pp) {
    long tmp = strtol(pp->eyr, NULL, 10);
    if (2031 > tmp && tmp > 2019) {
        return 1;
    } else {
        printf("invalid expiration date %s\n", pp->eyr);
        return 0;
    }
}

/* cid (Country ID) - ignored, missing or not. */
int Passport_verify_cid(struct Passport *pp) {
    return 1;
}

/* hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f. */
int Passport_verify_hcl(struct Passport *pp) {
    char *tmp = pp->hcl;
    if (strlen(pp->hcl) != 7) {
        printf("invalid hair color %s (hex too short)\n", pp->hcl);
        return 0;
    } else if (*tmp != '#') {
        printf("invalid hair color %s (expect #{hex})\n", pp->hcl);
        return 0;
    } else {
        for (int i=0 ; i<6 ; i++) {
            if (!isxdigit(*(++tmp))) {
                printf("invalid hair color %s (not hex digit %c)\n", pp->hcl, *(--tmp));
                return 0;
            }
        }
        return 1;
    }
}

/* ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth. */
int Passport_verify_ecl(struct Passport *pp) {
    if (strlen(pp->ecl) == 3 && (!strncmp(pp->ecl, "amb", 3) || !strncmp(pp->ecl, "blu", 3)
        || !strncmp(pp->ecl, "brn", 3) || !strncmp(pp->ecl, "gry", 3) || !strncmp(pp->ecl, "grn", 3)
        || !strncmp(pp->ecl, "hzl", 3) || !strncmp(pp->ecl, "oth", 3))) {
        return 1;
    } else {
        printf("invalid eye color: %s\n", pp->ecl);
        return 0;
    }
}

/* hgt (Height) - a number followed by either cm or in:
    If cm, the number must be at least 150 and at most 193.
    If in, the number must be at least 59 and at most 76. */
int Passport_verify_hgt(struct Passport *pp) {
    char *unit = pp->hgt;
    unit += strlen(pp->hgt) - 2;  // unit is the last 2 characters

    if (strlen(unit) != 2) {
        printf("invalid height %s, (unit len %ld)\n", pp->hgt, strlen(pp->hgt) - 2);
    } else {
        long value = strtol(pp->hgt, &unit, 10);
        if (!strncmp(unit, "cm", 2)) {
            if (194 > value && value > 149) {
                return 1;
            } else {
                printf("invalid height %s (number %ld)\n", pp->hgt, value);
            }
        } else if (!strncmp(unit, "in", 2)) {
            if (77 > value && value > 58) {
                return 1;
            } else {
                printf("invalid height %s (number %ld)\n", pp->hgt, value);
            }
        } else {
            printf("invalid height %s (unit %s)\n", pp->hgt, unit);
        }
    }
    return 0;
}

/* hash function for strings
    src: https://stackoverflow.com/questions/7666509/hash-function-for-string */
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

int parse_word_delimited(char **dst, char **src, char *dlm) {
    short end = strcspn(*src, dlm);
    assert(end);
    if (end) {
        *dst = strndup(*src, end);
    }
    return ++end; // do not include the delimiter
}

/* Parse them all, boss */
void parse_passports(char *raw, long long sz) {
    long valid_passports = 0, valid_passports_2 = 0;
    struct Passport *pp = Passport_create();
    char *key, *val;

    do {
        raw += parse_word_delimited(&key, &raw, ":");
        raw += parse_word_delimited(&val, &raw, "\n ");

        assert(strlen(key) && strlen(val));

        Passport_write_field(pp, key, val);
        free(key);
        free(val);

        if (*raw == '\n') {
            raw++;
            valid_passports += Passport_is_valid(pp);
            valid_passports_2 += Passport_is_valid2(pp);

            Passport_destroy(pp);
            pp = Passport_create();
        }

    } while (*raw);

    Passport_destroy(pp);

    printf("Valid passport count: %ld\n", valid_passports);
    printf("Valid passport count2: %ld\n", valid_passports_2);
}

int main(int agrc, char* argv[]) {
    FILE *file;
    long long filesize;
    long valid_passports; 
    char *text;

    file = fopen("input.txt", "rb");
    if (file == NULL) {
        fputs("File error", stderr);
        return EXIT_FAILURE;
    }
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    rewind(file);

    text = malloc(filesize);
    if (text == NULL) {
        fclose(file);
        fputs("Memory error", stderr);
        return EXIT_FAILURE;
    }
    fread(text, 1, filesize+1, file);
    fclose(file);
    text[filesize] = '\0';

    parse_passports(text, filesize);
    
    free(text);
    return EXIT_SUCCESS;
}
