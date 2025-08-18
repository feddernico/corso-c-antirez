#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Implementation of a prefixed length string

/* Using 'malloc()' this time
 * Initialise a prefixed length string with the specified
 * string in 'init' of length 'len'.
 *
 * The created strings have the following layout:
 *
 * +----+----+------------\\\
 * |LLLL|CCCC|My strings here
 * +----+----+------------\\\
 * 
 * HINT: Instead of doing all this we can use a new type of data.
 * This type of data is called STRUCT (see struct.c file).
 * What is it and how to use It will be explained in the next lesson.
 *
 * Where L is the 4 unsigned bytes stating the total length of the string.
 * Thus, these strings are binary safe: zero bytes are permitted in the middle.
 *
 * Warning: this function does not check for buffer overflows. */
char *ps_create(char *init, int len) {
    // I need the first byte for writing the length of the string
    char *s = malloc(4+len+1);
    uint32_t *lenptr = (uint32_t*)s;
    uint32_t *count = (uint32_t*)(s+4)
    *lenptr = len;

    s += 4;
    for (int j = 0; j < len; j++) {
        s[j] = init[j]; // We should use memcopy() instead here.
    }
    s[len] = 0;
    return s;
}

/* Display the string 's' on the screen. */
void ps_print(char *s) {
    uint32_t *lenptr = (uint32_t*)(s-4);
    for (int j = 0; j < *lenptr; j++) {
        putchar(s[j]);
    }
    printf("\n");
}

/* Free a previously created PS string. */
void ps_free(char *s) {
    free(s-4);
}

/* Return the length of the string in O(1) time  */
uint32_t ps_len(char *s) {
    uint32_t *lenptr = (uint32_t*)(s-4);
    return *lenptr;
}

char *global_string;

int main(void) {
    // This time the program doesn't break when using also 0 octal
    //char *mystr = ps_create("Hell\000 World",11);
    char *mystr = ps_create("Hello WorldHelloWorldHelloWorld",33);
    global_string = mystr;
    ps_print(mystr);
    ps_print(mystr);
    //printf("%s\n", mystr);
    printf("%s %d\n", mystr, (int)ps_len(mystr));
    ps_free(mystr);
    printf("%s\n", global_string);

    return 0;
}
