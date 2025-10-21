#include <stdio.h>

/* A pointer to a function contains the memory address that contains 
 * the machine code used by the function.*/

void hello (void) {
    printf("Hello!\n");
}

void baubau(void) {
    printf("Bau Bau!\n");
}

void call_n_times(int n, void(*x)(void)) {
    while(n--) {
        x();
    }
}

int main(void) {
    // this is a pointer to a function
    
    call_n_times(10, hello);
    call_n_times(10, baubau);
    return 0;
}


