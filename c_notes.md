## About getline.c
Aparently it is not explicitly part of the standard library but rather some POSIX extension,
for this reason it is not available on windows ._.


## Macro to get the number of elements in an arrray
```c
#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

```

## Removing trailing newline character from fgets() input
[https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input]
```c
Name[strcspn(Name, "\n")] = 0;

```
## Count occurences of char in string
[https://stackoverflow.com/questions/4235519/counting-number-of-occurrences-of-a-char-in-a-string-in-c/4235545]
```c
// the one I use
int scountc(char *string, char key) {
    int i;
    char *s = string;
    for (i = 0; s[i]; s[i]==key ? i++ : *s++);
    return i;
}

// based on this one liner missing declarations
for (i=0; s[i]; s[i]=='.' ? i++ : *s++);
```