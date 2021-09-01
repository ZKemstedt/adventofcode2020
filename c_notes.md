## About getline.c
Aparently it is not explicitly part of the standard library but rather some POSIX extension,
for this reason it is not available on windows ._.


## Macro to get the number of elements in an arrray
```c
#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

```

## Removing trailing newline character from fgets() input (or any newline-delimited char-array)
[source](https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input)
```c
some_string[strcspn(some_string, "\n")] = 0;

```

## Count occurences of char in string
[source](https://stackoverflow.com/questions/4235519/counting-number-of-occurrences-of-a-char-in-a-string-in-c/4235545)
```c
// source
for (i=0; s[i]; s[i]=='.' ? i++ : *s++)

// my implementation
int scountc(char *string, char key) {
    int i;
    char *s = string;
    for (i = 0; s[i]; s[i]==key ? i++ : *s++);
    return i;
}


```