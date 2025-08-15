#include <stdio.h>
#include <stdlib.h>

// Implementation of a prefixed length string

/* Initialise a prefixed length with the specified 
 * string in 'init' of length 'len'. 
 *
 * Warning: this function does not check for buffer overflows. */
void ps_init(char *s, char *init, int len) {
    // I want to record the length of the string between [0, 255]
    // otherwise I would have values [-128, +127]
    unsigned char *lenptr = (unsigned char*)s;
    // pointer derefentiation
    *lenptr = len;
    for (int j = 0; j < len; j++) {
        s[j+1] = init[j];
    }
}

/* Using 'malloc()' this time
 * Initialise a prefixed length string with the specified
 * string in 'init' of length 'len'.
 *
 * The created strings have the following layout:
 *
 * +-+------------\\\
 * |L|My strings here
 * +-+------------\\\
 *
 * Where L is the one unsigned byte stating the total length of the string.
 * Thus, these strings are binary safe: zero bytes are permitted in the middle.
 * 
 * Warning: this function does not check for buffer overflows. */
char *ps_create(char *init, int len) {
    // I need the first byte for writing the length of the string
    char *s = malloc(1+len+1);
    unsigned char *lenptr = (unsigned char*)s;
    *lenptr = len;
    for (int j = 0; j < len; j++) {
        s[j+1] = init[j];
    }
    s[len+1] = 0;
    return s;
}

/* Display the string 's' on the scree. */
void ps_print(char *s) {
    unsigned char *lenptr = (unsigned char*)s;
    for (int j = 0; j < *lenptr; j++) {
        putchar(s[j+1]);
    }
    printf("\n");
}

/* Return the pointer to the null terminated C string embedded
 * inside our PS string 's'. */
char *ps_getc(char *s) {
    return s+1;
}

int main(void) {
    // This time the program doesn't break when using also 0 octal
    //char *mystr = ps_create("Hell\000 World",11);
    char *mystr = ps_create("Hello WorldHelloWorldHelloWorld",33);
    ps_print(mystr);
    ps_print(mystr);
    //printf("%s\n", mystr);
    printf("%s\n", ps_getc(mystr));
    free(mystr);

    return 0;
}
