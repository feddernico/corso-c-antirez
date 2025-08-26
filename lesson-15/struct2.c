#include <stdio.h>
#include <stdlib.h>

/* The structure is one of the only examples where C
 * doesn't deal with numbers.
 * A structure is not a number, is a type of data.
 *
 * If I want to add a colour (unsigned char)
 * the internal layout is:
 *
 * +-+----+----+
 * |c|num |den |
 * +-+----+----+
 * you were expeting a 9 bytes
 * but it's actually a 12 bytes structure size
 * By default a structure member is recorded to a memory address
 * that is multiple of its size.
 *
 * So the actual layout looks like this:
 * +----+----+----+
 * |cPPP|num |den |
 * +----+----+----+
 * where P is a PADDING byte.
 *
 * Also the structure is aligned to the biggest type of its component.
 * This is because you can have array in structures.
 *
 * The way you declare fields in a structure is important
 * to make sure you don't waste space */
struct fract {
    int num;
    int den;
};

/* Create a new fraction, setting num and den as the numerator
 * and denominator of the fraction.
 * The function returns NULL on out of memory, otherwise the
 * fraction object is returned. */
struct fract create_fraction(int num, int den) {
    // This is to demonstrate that structures are
    // actually a type of data
    struct fract f;
    f.num = num;
    f.den = den;
    return f;
}

/* Simplify the provided fraction. */
void simplify_fraction(struct fract *f) {
    for (int d = 2; d <= f->num && d <= f->den; d++) {
        while (f->num % d == 0 &&
            f->den % d == 0)
        {
            f->num /= d;
            f->den /= d;
        }
    }
}

void print_fraction(struct fract *f) {
    printf("%d/%d\n", f->num, f->den);
}

int main(void) {
    // it's 8 byte long, because int num is 4 bytes
    // and int den is 4 bytes long.
    printf("%d\n", (int)sizeof(struct fract));

    struct fract a;
    struct fract *b = &a;
    // when you access fields in a structure you use a .
    // when you access them using a pointer you use a ->
    b->num = 1;
    b->den = 2;
    printf("%d/%d\n", a.num, a.den);

    // behind the scenes C copies the bytes from the structure
    // returned by create_fraction and puts them into f1.
    // When I was working with the pointer there was no implicit copy
    // This time there is.
    // So, we need to be careful when the structures are big,
    // bacause the program becomes extremely inefficient
    //
    // That's why the structure are passed using the pointer
    struct fract f1 = create_fraction(10,20);
    struct fract f2 = create_fraction(3,4);
    simplify_fraction(&f1);
    print_fraction(&f1);
    print_fraction(&f2);
    return 0;

// a quick way to create a commented block
#if 0
    int *f1 = create_fraction(10,20);
    int *f2 = create_fraction(3,4);
    simplify_fraction(f1);
    print_fraction(f1);
    print_fraction(f2);
    return 0;
#endif
}
