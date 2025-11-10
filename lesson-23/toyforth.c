#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TFOBJ_TYPE_INT 0
#define TFOBJ_TYPE_STR 1
#define TFOBJ_TYPE_BOOL 2
#define TFOBJ_TYPE_LIST 3
#define TFOBJ_TYPE_SYMBOL 4


/* ========================== Data structures =========================== */

typedef struct tfobj {
    int refcount;
    int type; // TFOBJ_TYPE_*
    union {
        int i;
        struct str {
            char *ptr;
            size_t len;
        } str;
        // we can use the list as a stack.
        struct list {
            // array of pointers to tfobj objects.
            struct tfobj **ele;
            size_t len;
        } list;
    };
} tfobj;

/* we need to have a program that given a list like "5 5 dup",
 * transforms the string into a tfobj object. */
typedef struct tfparser {
    char *prg;  // The program to compile into a list.
    char *p;    // Next token to parse.
} tfparser;

typedef struct tfctx {
    tfobj *stack; 
} tfctx;

/* ========================= Allocation wrappers ======================== */

void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1);
    }
    return ptr;
}

/* ====================== Object related functions ====================== 
 * The following functions allocate Toy Forth objects of different types. */

/* Allocate and initialise a new Toy Forth object. */
tfobj *createObject(int type) {
    tfobj *o = xmalloc(sizeof(tfobj));
    o->type = type;
    o->refcount = 1;
    return o;
}

tfobj *createStringObject(char *s, size_t len) {
    tfobj *o = createObject(TFOBJ_TYPE_STR);
    o->str.ptr = s;
    o->str.len = len;
    return o;
}

tfobj *createSymbolObject(char *s, size_t len) {
    tfobj *o = createStringObject(s, len);
    o->type = TFOBJ_TYPE_SYMBOL;
    return o;
}

tfobj *createIntObject(int i) {
    tfobj *o = createObject(TFOBJ_TYPE_INT);
    o->i = i;
    return o;
}

tfobj *createBoolObject(int i) {
    tfobj *o = createObject(TFOBJ_TYPE_BOOL);
    o->i = i;
    return o;
}

tfobj *createListObject(int i) {
    tfobj *o = createObject(TFOBJ_TYPE_LIST);
    o->list.ele = NULL;
    o->list.len = 0;
    return o;
}

/* =============================== Main ================================ */

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    tfobj *prg = compile(prgtext);
    exec(prgtext);
    return 0;
}
