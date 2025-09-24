#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct pls {
    // 8 bytes
    long len;
    // 8 bytes pointer to a string
    // char *str;
    // now we change it to an array of 20 characters
    char str[20];
};

#define HEXDUMP_CHARS_PER_LINE 8
void hexdump(void *p, size_t len) {
    unsigned char *byte = p;
    size_t po = 0;
    for (int j = 0; j < (int) len; j++) {
        // prints a number passed as an int as hex
        printf("%02X ", byte[j]);
        if ((j+1) % HEXDUMP_CHARS_PER_LINE == 0 || j == (int)len-1) {
            if (j == (int)len-1) {
                int pad = HEXDUMP_CHARS_PER_LINE -
                    (len % HEXDUMP_CHARS_PER_LINE);
                pad %= HEXDUMP_CHARS_PER_LINE;
                for (int i = 0; i < pad; i++) printf("~~ ");
            }
            printf("\t");
            for (size_t i = po; (int)i <= j; i++) {
                int c = isprint(byte[i]) ? byte[i] : '.';
                printf("%c", (char)c);
            }
            printf("\n");
            po = j+1;
        }
    }
}

int main(void) {
    struct pls s;

    // to identify the part of memory that is not part of the program
    memset(&s, 0xff, sizeof(s));

    s.len = 10;
    // +1 is for the NULL term
    // s.str = malloc(10+1);
    // now that we converted str into an array we don't need the malloc 
    // str will be converted into a pointer, a pointer to the array of 20 chars
    // -- first 8 bytes ---
    // 0A 00 00 00 00 00 00 00 31 32 33 34 35 36 37 38 39 30 00 00 00 00 00 00 00 00 00 00 00 00 00 00

    // transform this string into a pointer
    memcpy(s.str, "1234567890", 11);
    printf("%p\n", s.str);
    hexdump(&s, sizeof(s));
    return 0;
}


