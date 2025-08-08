#include <stdio.h>

int main(void) {
//    int x = 5;
    // extract the memory address from x
//    int *y = &x;
//    int **z = &y;
//    printf("x is store in %p and y is stored in %p\n", y, z);
//    printf("%d, %d, %d\n", (int)sizeof(x), (int)sizeof(y), (int)sizeof(z));
    
    char mystr[] = "AABBCCDDEEFF";
    // in C a name of an array, it's also a pointer to that array 
    // I am casting
    short *p = (short*)mystr;
    printf("At %p I can see: %s\n", mystr, mystr);

    // to access the various elements of mystr, I can do something like this
    //printf("%c%c", p[0], p[1]);

    // this will print the address at which the first letter of mystr is saved.
    printf("%d\n", *p);
    p += 4;
    printf("%d\n", *p);
    
    // the maths of pointers follows a peculiar maths 
    // when a pointer is incremented by 1, in reality this 1 will be multiplied
    // by the size of the base type of the pointer
    // if the pointer is short is 2 bytes, that means that +1 becomes +2 bytes
    printf("%d\n", p[2]);
    // if I point to something outside the program space 
    // I will get a Segmentation fault error.
    // printf("%d\n", p[-5694560596]);
    char *pp = mystr;
    printf("At the beginning p is %p\n", pp);
    while(*pp != 0) {
        putchar(*pp);
        pp++;
    }
    printf("\n");
    printf("At the end p is %p\n", pp);
    return 0;
}
