#include <stdio.h>

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

void display_hashes() {
    printf("pid: %ld\n", hash((unsigned char *) "pid"));
    printf("byr: %ld\n", hash((unsigned char *) "byr"));
    printf("iyr: %ld\n", hash((unsigned char *) "iyr"));
    printf("eyr: %ld\n", hash((unsigned char *) "eyr"));
    printf("cid: %ld\n", hash((unsigned char *) "cid"));
    printf("ecl: %ld\n", hash((unsigned char *) "ecl"));
    printf("hcl: %ld\n", hash((unsigned char *) "hcl"));
    printf("hgt: %ld\n", hash((unsigned char *) "hgt"));
}
