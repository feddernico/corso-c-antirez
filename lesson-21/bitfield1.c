#include <stdio.h>
#include <string.h>
#include <limits.h>

struct foo {
    /* I am asking C an integer of the number of bits I specify.
     * a = 4-bit integer, 2^4-1: 0-15 possible values.
     * b, c = 8-bit integers, 2^5-1: 0-255 possible values. 
     *
     * Why this might be useful? 
     * 1) To save memory
     * 2) There are protocols, or headers, where each part 
     *    contains certain pieces of information.
     * In the second case the problem could be if the system is
     * big endian or little endian. Here there is an example to test this:
     * https://sites.uclouvain.be/SystInfo/usr/include/netinet/ip.h.html */
    unsigned char a:4;
    unsigned char b:4;
    unsigned char c:8;
};

int main(void) {
    struct foo f;
    /* In C there is a rule:
     * To increment an unsigned type beyond its maximum dimension, 
     * will have the effect of getting 0 (wrapping around).
     * If the type is signed, the operation will be undefinied. */
    f.a = 16;
    f.b = 2;
    f.c = 3;

    printf("%d %d %d\n", f.a, f.b, f.c);
    return 0;
}
