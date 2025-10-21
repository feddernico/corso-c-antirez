#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Why pointers to functions are that important in C?
 * Let's have a look at this example */

/* const before the pointer means that the function doesn't change the pointer
 * 00001111222233334444 .... 9999 */
int compare_integers(const void *a, const void *b) {
    // I convert the pointers to the correct values.
    const int *ap = a;
    const int *bp = b;

    /* The interface of the function is that it should return: 
     * 0: if the numbers are the same
     * a number > 0: if a is greater than b
     * a number < 0: if b is greater than a */
    if (ap[0] > bp[0]) return 1;
    else if (ap[0] < bp[0]) return -1;
    else return 0;
}

int main(void) {
    int a[10];
    for (int j = 0; j < 10; j++)
        /* using a mask with 15 to have the first 4 bits equal to one.
         * This means that I will only have numbers between 0 and 15 */
        a[j] = rand() & 15;

    // try an edge case with INT MIN and MAX
    a[2] = INT_MAX;
    a[5] = INT_MIN;
    
    /* Now, to order this array I need to use the qsort function. */
    qsort(a, 10, sizeof(int), compare_integers);
    
    for (int j = 0; j < 10; j++)
        printf("%d ", a[j]);

    printf("\n");
    return 0;
}


