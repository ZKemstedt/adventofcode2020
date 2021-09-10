struct Passport;

struct Passport *Passport_create();
void Passport_destroy(struct Passport *pp);
void Passport_write_field(struct Passport *pp, char *key, char *val);
int Passport_verify_pid(struct Passport *pp);
int Passport_verify_byr(struct Passport *pp);
int Passport_verify_iyr(struct Passport *pp);
int Passport_verify_eyr(struct Passport *pp);
int Passport_verify_cid(struct Passport *pp);
int Passport_verify_hcl(struct Passport *pp);
int Passport_verify_ecl(struct Passport *pp);
int Passport_verify_hgt(struct Passport *pp);

int parse_word_delimited(char **dst, char **src, char *dlm);
void parse_passports(char *raw, long long sz);
unsigned long hash(unsigned char *str);
