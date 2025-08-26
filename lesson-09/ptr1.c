#include <stdio.h>

void incr(int *p) {
    *p = *p + 1;
}


int main(void) {
    int x = 5;
    // this is a way to create a pointer variable 
    // initialised to a null pointer. You can use both 0 or NULL.
    int *y = NULL;

    printf("x was %d\n", x);

    // This means "give me the memory address of x".
    y = &x;
    printf("x is stored at the address %p\n", y);

    // why it's important to declare the type of pointers?
    // because in this case you can write 10 to the memory address
    // allocated to y.
    *y = 10;

    // this can also be written like this.
    // If you write inside y[1], you write in the next byte of memory
    // so this might potentially crash the program
    y[0] = 10;

    printf("x now is %d\n", x);

    // Now why using a pointer is useful? Couldn't we just do x = 10?
    // In the previous case yes, but look at this example
    x = 5;
    printf("x was %d\n", x);
    incr(&x);
    printf("x now is %d\n", x);
    // basically you can increment a variable by just using the pointer
    // and modifying the variable that is stored there.

    return 0;
}
