#include <stdio.h>

/* 8-bit number
 * |76543210|
 *  00010110
 *
 *  Reminder of the numerical basis, useful to understand Block 1:
 *  2 bytes, like the first two numbers in str
 *  01 01
 *  both of them have values 0-255, but the one on the left
 *  needs to be multiplied by 256 because of its position
 *  
 */
int main(void) {
    // Block 1.
    // This block of code prints the ascii value fo the 
    //char str[] = {1, 1, 2, 2};
    //short *s = (short*)str;
    //printf("%d %d\n", s[0], s[1]);
   
    // This way I implemented a pre-fixed length string
    // the length of the string is defined by the first octal value \017
    char str[] = "\017Hello00\0000000123";
    // if I add a 0 in octal value, the program will stop once it reaches that point
    //str[] = "Hello\017000123";
    char *p = str;
    printf("My string len is %d\n", p[0]);
    int len = *p++;
    for (int j=0; j < len; j++) {
        putchar(p[j]);
    }
    printf("\n");

    // same as writing while(*p != 0)
    //while(*p) {
    //    // This will print the decimal number relative to the ascii table for each character
    //    printf("%d ", *p);
    //    //putchar(*p);
    //    p++;
    //}
    //printf("\n");
    
    return 0;
}
