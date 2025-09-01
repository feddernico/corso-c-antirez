#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// This structure have fields that are naturally aligned
struct pls {
    // 4 byte field aligned to offset 0
    uint32_t len;
    // 4 byte field aligned to offset 4
    uint32_t refcount;
    /* This declaration is in style C99 a pointer to offset 8 of type char
     * but we don't know how many byte will be contained
     * the size of the string will be controlled by the malloc */
    uint32_t magic;
    char str[];
};

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
    /* The +1 is for the NULL terminator */
    struct pls *p = malloc(sizeof(struct pls)+len+1);
    p->len = len;
    p->refcount = 1;
    p->magic = 0xDEADBEEF;
    for (int j = 0; j < len; j++) {
        p->str[j] = init[j]; // We should use memcopy() instead here.
    }
    p->str[len] = 0;
    return p->str;
}

/* Display the string 's' on the screen. */
void ps_print(char *s) {
    struct pls *p = (struct pls*)(s - sizeof(*p)); 
    for (uint32_t j = 0; j < p->len; j++) {
        putchar(p->str[j]);
    }
    printf("\n");
}

/* Free a previously created PS string. */
void ps_free(char *s) {
    // free needs to be called at the beginning of the memory address
    free(s-sizeof(struct pls));
}

/* Check that a PS string looks valid. */
void ps_validate(struct pls *p) {
    if (p->magic != 0xDEADBEEF) {
        printf("INVALID STRING: Aborting\n");

    }
}

/* Decrease the reference count of the string object by one
 * and frees the oject if the refcount reached 0. */
void ps_release(char *s) {
    struct pls *p = (struct pls*)(s - sizeof(*p));
    ps_validate(p);

    printf("Current refcount is %d\n", (int)p->refcount);
    if (p->refcount == 0) {
        printf("ABORTED ON FREE ERROR\n");
        exit(1);
    }
    
    p->refcount--;
    if (p->refcount == 0) {
        p->magic = 0;
        ps_free(s);
    }
}

/* Increase the reference count of the string object. */
void ps_retain(char *s) {
    struct pls *p = (struct pls*)(s - sizeof(*p));
    printf("Current refcount is %d\n", (int)p->refcount);
    if (p->refcount == 0) {
        printf("ABORTED ON RETAIN OF ILLEGAL STRING\n");
        exit(1);
    }
    p->refcount++;
}

/* Return the length of the string in O(1) time  */
uint32_t ps_len(char *s) {
    struct pls *p = (struct pls*)(s - sizeof(*p)); 
    return p->len;
}

char *global_string;

int main(void) {
    // This time the program doesn't break when using also 0 octal
    //char *mystr = ps_create("Hell\000 World",11);
    char *mystr = ps_create("Hello WorldHelloWorldHelloWorld",33);
    /* I created a new ownership by assigning it to global_string
     * so, I will need to use ps_retain to increase the reference count */
    global_string = mystr;
    ps_retain(mystr);

    ps_print(mystr);
    ps_print(mystr);
    //printf("%s\n", mystr);
    printf("%s %d\n", mystr, (int)ps_len(mystr));
    ps_release(mystr);
    printf("%s\n", global_string);
    ps_release(mystr);
    ps_release(mystr);

    return 0;
}
