#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct STRING_S
{
    char* data;
    uint32_t length;
} STRING;

#define a_str "Hello"
#define b_str " World"

void print_str(STRING x)
{
    printf("%d - %s\n", x.length, x.data);
}

int main()
{
    STRING a;
    a.length = strlen(a_str);
    a.data = (char*) malloc(a.length * sizeof(char));
    strncpy(a.data, a_str, a.length);

    STRING b;
    b.length = strlen(b_str);
    b.data = (char*) malloc(b.length * sizeof(char));
    strncpy(b.data, b_str, b.length);

    STRING add;

    add.length = a.length + b.length;

    add.data = (char*) malloc(add.length * sizeof(char));

    strncpy(add.data, a.data, a.length);
    strncat(add.data, b.data, b.length);

    print_str(a);
    print_str(b);
    print_str(add);

    free(a.data);
    free(b.data);
    free(add.data);

    return 0;
}