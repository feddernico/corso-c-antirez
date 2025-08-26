#include <stdio.h>

// crea un loop usando if e ricorsione
void conta_vanilla(int start, int end) {
    if (start > end) return;
    printf("%d\n", start);
    conta_vanilla(start+1, end);
}

// tail call optimisation
void conta(int start, int end) {
iterate:
    if (start > end) return;
    // it always use the same memory address
    printf("%d %p\n", start, &start);
    start = start+1;
    goto iterate;
}

int main(void) {
    conta(0, 9);
    
    // while loop
    int i = 0;
    while (i < 10) {
        printf("%d\n", i);
        i++;
    }
    printf("\n");
    
    // for loop
    for(i = 0; i < 10; i++) {
        printf("%d\n", i);
    }
    printf("\n");

    // for loop without initialisation,
    // rule to stop it
    // nor increment
    for(;;) {
        if (i >= 10) break;
        printf("%d\n", i);
        i++;
    }
    printf("\n");
    
    
    // use the index value to check if a value was found
    int a[] = {1, 5, 8, 4, 9, 0};
    for (i = 0; a[i] != 0; i++) {
        if (a[i] == 8) break;
    }
    if (a[i] == 0) {
        printf("Non trovato\n");
    } else {
        printf("Trovato\n");
    }
    
    // do-while loop
    // do {
    // 
    // } while();
    
    i = 5;
    switch(i) {
        case 5: 
        // you can add a variable in the case only if you add a block
        {
            int j = 10;
            printf("E' un cinque (%d)\n", j);
            printf("Si, proprio un bel 5\n");
            break;
        }
        
        case 7: printf("E' un sette\n"); break;
        default: printf("Qualche altro numero\n"); break;
    }
    
    return 0;
}
