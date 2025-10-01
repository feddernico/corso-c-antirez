#include <stdio.h>

// create a specific errorcode
// this becomes an alias of an int by using typedef
typedef int errorcode;

typedef struct {
    int n;
    int d;

} fract;

typedef fract *fractptr;

errorcode foo(void) {
    return -20;
}

int main(void) {
    fract f;
    fractptr fp = &f;
    f.n = 10;
    f.d = 20;
    printf("%d/%d my fraction is stored at %p\n", f.n, f.d, fp);

    errorcode a = foo();
    // variatic function
    printf("%d\n", a);
}
