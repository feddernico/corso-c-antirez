#include <limits.h>
#include <stdio.h>
#include <string.h>

/* How data is structured in memory?
 * IIIIAAAA */
struct foo {
    /* I am asking that the fields of my structure foo which are
     * i and a, need to start in the same offset (0). 
     * This means that if I write in i I overwrite a and viceversa. 
     * 
     * Interesting fact an anonym union couldn't be written before C99. 
     * In general union should have a name */
    union {
        int i;
        unsigned char a[4];
    };
};

int main(void) {
    struct foo f;
    
    f.i = 10;
    // memcpy(f.a, "abcd", 4);
    /* in this case f.a is the pointer to where the array a starts.
     * It's calculated at compile time by adding 4 bytes to f */
    printf("%d [%d %d %d %d]\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);
    /* this macbook is little endian so the least significative bytes 
     * are written first. So that's why you see:
     * 10 [10 0 0 0] */
    return 0;
}
