#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
#include <assert.h>
#include "hash.c"

#define KLEN_MAX 3
#define VLEN_MAX 9

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

void pp_set_pid(struct Passport *pp, char *val);
void pp_set_byr(struct Passport *pp, char *val);
void pp_set_iyr(struct Passport *pp, char *val);
void pp_set_eyr(struct Passport *pp, char *val);
void pp_set_cid(struct Passport *pp, char *val);
void pp_set_hcl(struct Passport *pp, char *val);
void pp_set_ecl(struct Passport *pp, char *val);
void pp_set_hgt(struct Passport *pp, char *val);

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

/* forwards attempts to set various pp fields to their respective setters
 * numbers are obtained using a hash function on the fields, see hash.c
 */
void set_passport_field_2(struct Passport *pp, char *key, char *val) {
    switch (hash((unsigned char *) key)) {
    case 193502530: pp_set_pid(pp, val); break;
    case 193487826: pp_set_byr(pp, val); break;
    case 193495449: pp_set_iyr(pp, val); break;
    case 193491093: pp_set_eyr(pp, val); break;
    case 193488373: pp_set_cid(pp, val); break;
    case 193490361: pp_set_ecl(pp, val); break;
    case 193493628: pp_set_hcl(pp, val); break;
    case 193493768: pp_set_hgt(pp, val); break;
    default:
        break;
    }
}

void set_passport_field(struct Passport *pp, char *key, char *val) {
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

/* returns 1 if all fields are set, except cid and hgt_unit wich are ignored */
int validate_passport(struct Passport *pp) {
    if (!(pp->hcl == NULL) && !(pp->byr == NULL) && !(pp->iyr == NULL) && !(pp->pid == NULL)
     && !(pp->eyr == NULL) && !(pp->hgt == NULL) && !(pp->ecl == NULL)) {

        printf("valid :)\n");
        return 1;
    } else {
        printf("invalid :/\n");
        return 0;
    }
}

/* set passport id, contains checks, will do nothing if the input is invalid */
void pp_set_pid(struct Passport *pp, char *val) {
    int c;
    if (strlen(val) > 9) {
        printf("invalid pid %s (len %lu)\n", val, strlen(val));
        return;
    }
    for (c=0 ; *val && c<10 ; c++) {
        switch (*val) {
            case '0': case '1': case '2':
            case '3': case '4': case '5':
            case '6': case '7': case '8':
            case '9': continue;
            default:
                printf("invalid pid %s (not a digit: %c)\n", val, *val);
                return;
        }
    }
    if (c == 10) {
        long tmp = strtoul(val, NULL, 10);
        pp->pid = strdup(val);
    } else {
        printf("invalid pid %s (n_digits: %d)\n", val, c);
    }
}

/* set birth year, contains checks, will do nothing if the input is invalid */
void pp_set_byr(struct Passport *pp, char *val) {
    long tmp = strtol(val, NULL, 10);
    if (2003 > tmp && tmp > 1919) {
        pp->byr = strdup(val);
    } else {
        printf("invalid birth year %s\n", val);
    }
}

/* set issue year, contains checks, will do nothing if the input is invalid */
void pp_set_iyr(struct Passport *pp, char *val) {
    long tmp = strtol(val, NULL, 10);
    if (2021 > tmp && tmp > 2009) {
        pp->iyr = strdup(val);
    } else {
        printf("invalid issue year %s\n", val);
    }
}

/* set expiration year, contains checks, will do nothing if the input is invalid */
void pp_set_eyr(struct Passport *pp, char *val) {
    long tmp = strtol(val, NULL, 10);
    if (2031 > tmp && tmp > 2019) {
        pp->eyr = strdup(val);
    } else {
        printf("invalid expirate date %s\n", val);
    }
}

/* cid is always ignored */
void pp_set_cid(struct Passport *pp, char *val) {
    return;
}

/* set hair color, contains checks, will do nothing if the input is invalid */
void pp_set_hcl(struct Passport *pp, char *val) {
    if (*val != '#') {
        printf("invalid hair color %s (expect #{hex})\n", val);
    } else if (strlen(val) != 7) {
        printf("invalid hair color %s (hex too short)\n", val);
    } else {
        val++;
        long tmp = strtoul(val, NULL, 16);
        if (UINT32_MAX > tmp > 0) {     // NOTE can still fail
            pp->hcl = strdup(val);
        } else {
            printf("invalid hair color %s (invalid hex)\n", val);
        }
    }
}

/* set eye color, contains checks will do nothing if the input is invalid */
void pp_set_ecl(struct Passport *pp, char *val) {
    if (strlen(val) == 3 && ( strncmp(val, "amb", 3) || strncmp(val, "blu", 3)
        || strncmp(val, "brn", 3) || strncmp(val, "gry", 3) || strncmp(val, "grn", 3)
        || strncmp(val, "hzl", 3) || strncmp(val, "oth", 3))) {
        pp->ecl = strdup(val);
    } else {
        printf("invalid eye color: %s\n", val);
    }
}

/* set height and height unit, contains checks, will do nothing if the input is invalid */
void pp_set_hgt(struct Passport *pp, char *val) {
    char *end = val;
    end += strlen(val) - 2;  // hgt_unit is the last 2 characters
    if (strlen(end) != 2) {
        printf("invalid height %s, (unit len %ld)\n", val, strlen(val) - 2);
        return;
    }

    long tmp = strtol(val, &end, 10); // properly read the numbers

    if (*end == 'c' && *(end+1) == 'm') {
        if (194 > tmp && tmp > 149) {
            pp->hgt = strndup(val, strlen(val) - 2);
        } else {
            printf("invalid height %s (number %ld)\n", val, tmp);
        }
    } else if (*end == 'i' && *(end+1) == 'n') {
        if (77 > tmp && tmp > 59) {
            pp->hgt = strndup(val, strlen(val) - 2);
        } else {
            printf("invalid height %s (number %ld)\n", val, tmp);
        }
    } else {
        printf("invalid height %s (unit %s)\n", val, end);
    }
}


int parse_word_delimited(char **dst, char **src, char *dlm) {
    short end = strcspn(*src, dlm);
    // printf("len: %d\n", end);
    assert(end);
    if (end) {
        *dst = strndup(*src, end);
        // printf("string: %s\n", *dst);
    }
    return ++end; // include the delimiter
}

/* Parse them all, boss */
void parse_passports(char *raw, long long sz) {
    long valid_passports = 0, valid_passports_2 = 0;
    struct Passport *pp = Passport_create();
    struct Passport *pp2 = Passport_create();
    char *key, *val;

    do {
        raw += parse_word_delimited(&key, &raw, ":");
        raw += parse_word_delimited(&val, &raw, "\n ");

        assert(strlen(key) && strlen(val));

        set_passport_field(pp, key, val);
        set_passport_field_2(pp2, key, val);
        free(key);
        free(val);

        if (*raw == '\n') {
            raw++;
            printf("new passport\n");
            valid_passports += validate_passport(pp);
            valid_passports_2 += validate_passport(pp2);

            if (!*raw) {
                printf("done\n");
                break;
            }

            // a realloc or simply overwrite would be faster but this feels easier
            Passport_destroy(pp);
            Passport_destroy(pp2);
            pp = Passport_create();
            pp2 = Passport_create();
        }

    } while (*raw);

    Passport_destroy(pp);
    Passport_destroy(pp2);

    printf("Valid passport count: %ld\n", valid_passports);
    printf("Valid passport count2: %ld\n", valid_passports_2);
}


        // long newline = hash((unsigned char *) "\n");
        // long key = hash((unsigned char *) *raw); 
        // if (newline == key) {
        //     printf("new passport?\n");
        //     raw++;
        //     valid_passports += validate_passport(pp);

        //     Passport_destroy(pp);
        //     pp = Passport_create();
        // }


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
