#include <stdio.h>

// argc: is the number of parameters passed from the command line
// argv contains an array of memory addresses (the explanation in the tac.md file) 
int main(int argc, char **argv) {
    for (int i=0; i < argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }
}
