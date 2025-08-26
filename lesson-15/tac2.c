#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* With this structure we build a new abstraction 
 * where we are uninterested on the memory logic that will be dealt by malloc. 
 * This is what we call a linked list.
 * In terms of algoritmic complexity fgets is O(n), 
 * then O(n) to navigate the file from the last to the first line.
 * But at the moment it allocates the whole file in memory. */
struct line {
    char *s;
    struct line *next;
};

int main(int argc, char **argv) {
    /* to open files in C we suppose that argc is equal to 2.
     * That's because you will have the name of the program running 
     * and the name of the file we want to open. */
    if (argc != 2) {
        printf("Missing file name\n");
        return 1;
    }

    /* So we declare a pointer of type FILE.
     * We can use this type of pointer because we use a keyword called typedef
     * In reality `FILE` is a `struct`, but with typedef we can use the name 
     * without repeating struct all the time. */
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("The file doesn't exist.\n");
        return 1;
    }
    
    // in order to read each line of a file I need a buffer
    char buf[1024];
    /* This is the head of my list. So, the first time this is will be NULL,
     * as there is nothing apart from the first line recorded. */
    struct line *head = NULL;
    /* this call to fgets fills the buffer with the next line of the file.
     * When the file will be over I will get an `EOF` 
     * and fgets will return `NULL`. */
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        struct line *l = malloc(sizeof(struct line));
        size_t linelen = strlen(buf);
        /* I am using an arrow because this is a pointer to strcut
         * strlen returns the length of this buffer. 
         * So it searches for the first byte that is 0 
         * and returns that char pointer + 1 because there is also
         * the null terminator. This is to create enough space for the line. */
        l->s = malloc(linelen+1);
        // then I copy the line using this for loop
        for (size_t j = 0; j <= linelen; j++) {
            l->s[j] = buf[j];
        }
        l->next = head;
        // the head becomes the last node read every time.
        head = l;
    }
    fclose(fp);

    while(head != NULL) {
        printf("%s", head->s);
        head = head->next;
    }
    return 0;
}
