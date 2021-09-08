#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h> 
#include "hash.c"

#define DEBUG 0

/*
    Collection of thoughts

    lots of memory shenanigans
    I wish I was more used to pointer-argument syntax

    currently breaks at line 145 (and possibly other places)
*/

struct passport {
    long pid;       // passport id
    long hcl;       // hair color
    int byr;        // birth year
    int iyr;        // issure year
    int eyr;        // expiration year
    int cid;        // country id
    short hgt;      // height (number)
    char hgt_unit[3];   // height (unit)
    char ecl[4];        // eye color
};

/* returns true is all fields are set, except cid and hgt_unit wich are ignored */
bool pp_is_valid(struct passport *pp) {
    if (pp->hcl && pp->byr && pp->iyr && pp->eyr && pp->cid && pp->hgt && pp->ecl)
        return true;
    return false;
}

/* set passport id, contains checks, will do nothing if the input is invalid */
void pp_set_pid(struct passport *pp, char *val) {
    long tmp = strtoul(val, NULL, 10);
    if (LONG_MAX > tmp > 0)
        pp->pid = tmp;
}

/* set birth year, contains checks, will do nothing if the input is invalid */
void pp_set_byr(struct passport *pp, char *val) {
    long tmp = strtol(val, NULL, 10);
    if (UINT16_MAX > tmp > 0)
        pp->byr = tmp;
}

/* set issue year, contains checks, will do nothing if the input is invalid */
void pp_set_iyr(struct passport *pp, char *val) {
    long tmp = strtol(val, NULL, 10);
    if (UINT16_MAX > tmp > 0)
        pp->iyr = tmp;
}

/* set expiration year, contains checks, will do nothing if the input is invalid */
void pp_set_eyr(struct passport *pp, char *val) {
    long tmp = strtol(val, NULL, 10);
    if (UINT16_MAX > tmp > 0)
        pp->eyr = tmp;
}

/* set country id, contains checks, will do nothing if the input is invalid */
void pp_set_cid(struct passport *pp, char *val) {
    long tmp = strtol(val, NULL, 10);
    if (UINT16_MAX > tmp > 0)
        pp->cid = tmp;
}

/* set hair color, contains checks, will do nothing if the input is invalid */
void pp_set_hcl(struct passport *pp, char *val) {
    if (*val != '#')
        return; // all haircolors start with a #
    val++;
    long tmp = strtoul(val, NULL, 0); // TODO FIXME
    if (UINT32_MAX > tmp > 0)
        pp->hcl = tmp;
}

/* set eye color, contains checks will do nothing if the input is invalid */
void pp_set_ecl(struct passport *pp, char *val) {
    if (strlen(val) != 3)
        return; // all eyeclors are 3 letters long
    strncpy(pp->ecl, val, 3);
    pp->ecl[3] = '\0';
}

/* set height and height unit, contains checks, will do nothing if the input is invalid */
void pp_set_hgt(struct passport *pp, char *val) {
    char *end = val;
    end += strlen(val) - 2;  // hgt_unit is the last 2 characters
    // if (strlen(end) != 2)
    //     return;

    long tmp = strtol(val, &end, 10); // properly read the numbers
    if (UINT16_MAX > tmp > 0)          
        pp->hgt = tmp;
        strncpy(pp->hgt_unit, end, 2);
        pp->hgt_unit[2] = '\0';
}

/* forwards attempts to set various pp fields to their respective setters
 * numbers are obtained using a hash function on the fields.
 * https://stackoverflow.com/questions/7666509/hash-function-for-string
 */
void pp_set_field(struct passport *pp, char *key, char *val) {
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

/* Returns a string pointer to the part of the string before the delimiter, NULL on failure */
/* char *parse_word_delimited(char **word, char **raw, char *dlm, long long **traveled) {
    short end = strcspn(*raw, dlm);    // find delimiter
    if (end) {
        *word = malloc(end * sizeof(char) + 1); // alloc
        if (*word == NULL)
            return NULL;
        memcpy(*word, *raw, end);        // copy towards it
        *word[end] = '\0';               // terminate string
        (*raw) += end + 1;                 // walk pointer: word + dlm
        (**traveled) += end + 1;         // walk counter: word + dlm
        return *word;                    // return ptr
    }
    return NULL;
}
 */
void parse_word_delimited(char **word, char **raw, char *dlm, long long **traveled) {
    short end = strcspn(*raw, dlm);    // find delimiter
    if (end) {
        *word = calloc(end + 1, sizeof(char)); // alloc
        if (*word == NULL)
            return;
        memcpy(*word, *raw, end);        // copy raw -> word
        *word[end] = '\0';               // terminate string

        for(int i=0 ; i<=end ; i++) {
            (*raw)++;
        }
        // *(+=raw) += end + 1;                  // walk pointer: word + dlm
        
        (**traveled) += end + 1;            // walk counter: word + dlm
    }
}


/* Returns NULL on error */
bool parse_kv(struct passport *pp, char **raw, long long *traveled, long long sz) {
    char *key = NULL;
    char *val = NULL;
    bool ret = false;

    parse_word_delimited(&key, raw, ":", &traveled);
    if (key == NULL)
        goto done;
    parse_word_delimited(&val, raw, "\n ", &traveled);
    if (val == NULL)
        goto done;
    pp_set_field(pp, key, val);
    ret = true;

    if (DEBUG) {
        printf("[ %lld / %lld ] key: %s, val: %s, next: %c",
               *traveled, sz, key, val, **raw);
    }

done:
    if (key != NULL)
        free(key);
        key = NULL;
    if (val != NULL)
        free(val);
        val = NULL;
    return ret;
}

/* Returns 1 if valid, 0 if invalid, NULL on error */
bool parse_passport(char **raw, long long *traveled, long long sz) {   
    struct passport pp = { 0, 0, 0, 0, 0, 0, 0, "\0\0\0", "\0\0\0\0" };
    if (**raw == '\n')
        raw++;
    while (**raw && **raw != '\n' && *traveled + 1 < sz) {
        if(!parse_kv(&pp, raw, traveled, sz))
            return false;
    }
    return pp_is_valid(&pp);
}

/* Parse them all, boss */
long parse_passports(char *raw, long long sz) {
    long long traveled = 0;
    long valid_passports = 0;
    
    while (traveled + 1 < sz && *raw) {
        valid_passports += parse_passport(&raw, &traveled, sz);
    }
    return valid_passports;
}

int main(int agrc, char* argv[]) {
    FILE *file;
    long long filesize;
    long valid_passports; 
    char *text, *tmp;

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

    tmp = text;
    valid_passports = parse_passports(tmp, filesize);
    printf("Valid passport count: %ld\n", valid_passports);

    free(text);
    return EXIT_SUCCESS;
}
