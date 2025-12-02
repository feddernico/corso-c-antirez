#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

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

/* Function table entry: each of these entries represents a symbol name
 * associated with a function implementation.
 * We use the first letter as a capital because it's a global variable. */
struct tfctx;
typedef struct FunctionTableEntry {
    tfobj *name;
    void (*callback) (struct tfctx *ctx, tfobj *name);
    tfobj *user_func;
} tffuncentry;

struct FunctionTable {
    tffuncentry **func_table;
    size_t func_count;
};

/* Our execution context. */
typedef struct tfctx {
    tfobj *stack;
    struct FunctionTable *functable;
} tfctx;

/* ========================= Function prototypes ======================== */

void retain(tfobj *o);
void release(tfobj *o);

/* ========================= Allocation wrappers ======================== */

void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1);
    }
    return ptr;
}

void *xrealloc(void *oldptr, size_t size) {
    void *ptr = realloc(oldptr, size);
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

/* Free an object and all the other nested objects. */
void freeObject(tfobj *o) {
    switch(o->type) {
    case TFOBJ_TYPE_LIST:
        for(size_t j = 0; j < o->list.len; j++) {
            tfobj *ele = o->list.ele[j];
            release(ele);
        }
        break;
    case TFOBJ_TYPE_SYMBOL:
    case TFOBJ_TYPE_STR:
        printf("%s", o->str.ptr);
        free(o->str.ptr);
        break;
    }
    free(o);
}

void retain(tfobj *o) {
    o->refcount++;
}

void release(tfobj *o) {
    assert(o->refcount > 0);
    o->refcount--;
    if (o->refcount == 0) freeObject(o);
}

void printObject(tfobj *o) {
    switch(o->type) {
    case TFOBJ_TYPE_INT:
        printf("%d", o->i);
        break;
    case TFOBJ_TYPE_LIST:
        printf("[");
        for(size_t j = 0; j < o->list.len; j++) {
            tfobj *ele = o->list.ele[j];
            printObject(ele);
            if (j != o->list.len-1)
                printf(" ");
        }
        printf("]");
        break;
    case TFOBJ_TYPE_STR:
        printf("\"%s\"", o->str.ptr);
        break;
    case TFOBJ_TYPE_SYMBOL:
        printf("%s", o->str.ptr);
        break;
    default:
        printf("?");
        break;
    }
}


/* ========================== String object ============================= */

tfobj *createStringObject(char *s, size_t len) {
    tfobj *o = createObject(TFOBJ_TYPE_STR);
    o->str.ptr = xmalloc(len+1);
    o->str.len = len;
    memcpy(o->str.ptr, s, len);
    o->str.ptr[len] = 0;
    return o;
}

tfobj *createSymbolObject(char *s, size_t len) {
    tfobj *o = createStringObject(s, len);
    o->type = TFOBJ_TYPE_SYMBOL;
    return o;
}

/* Compare the two string objects 'a' and 'b', returns 0 if they are 
 * the same, '1' if a > b,  '-1' if a < b. The comparison is performed
 * using memcmp(). */
int compareStringObject(tfobj *a, tfobj *b) {
    size_t minlen = a->str.len < b->str.len ? a->str.len : b->str.len;
    int cmp = memcmp(a->str.ptr, b->str.ptr, minlen);

    if (cmp == 0) {
        if (a->str.len == b->str.len) return 0;
        else if (a->str.len > b->str.len) return 1;
        else return -1;
    } else {
        if (cmp < 0) return -1;
        else return 1;
    }
}

/* =========================== List object ============================= */

tfobj *createListObject(void) {
    tfobj *o = createObject(TFOBJ_TYPE_LIST);
    o->list.ele = NULL;
    o->list.len = 0;
    return o;
}

/* Add the new element at the end of the list 'list'. 
 * It is up to the caller to increment the reference count of the 
 * element added to the list, if needed.*/
void listPush(tfobj *l, tfobj *ele) {
    l->list.ele = xrealloc(l->list.ele, sizeof(tfobj*) * (l->list.len+1));
    l->list.ele[l->list.len] = ele;
    l->list.len++;
}


/* ================ Turn program into toy forth list =================== */

void parseSpaces(tfparser *parser) {
    while(isspace(parser->p[0])) parser->p++;
}

#define MAX_NUM_LEN 128
tfobj *parseNumber(tfparser *parser) {
    char buf[MAX_NUM_LEN];
    char *start = parser->p;
    char *end;
    
    if (parser->p[0] == '-') parser->p++;
    while(parser->p[0] && isdigit(parser->p[0])) parser->p++;
    end = parser->p;
    int numlen = end-start;
    if (numlen >= MAX_NUM_LEN) return NULL;

    memcpy(buf, start, numlen);
    buf[numlen] = 0;

    tfobj *o = createIntObject(atoi(buf));
    return o;
}

/* Return true if the character 'c' is one of the characters 
 * acceptable for our symbols. */
int is_symbol_char(char c) {
    char symchars[] = "+-*/%";
    return isalpha(c) || strchr(symchars, c) != NULL;
}

tfobj *parseSymbol(tfparser *parser) {
    char *start = parser->p;
    while(parser->p[0] && is_symbol_char(parser->p[0])) parser -> p++;
    int len = parser->p-start;

    return createSymbolObject(start, len);
}

tfobj *compile(char *prg) {
    tfparser parser;
    parser.prg = prg;
    parser.p = prg;

    tfobj *parsed = createListObject();
    
    while(parser.p) {
        tfobj *o;
        char *token_start = parser.p;

        parseSpaces(&parser);
        if (parser.p[0] == 0) break;  // End of program reached.
        if (isdigit(parser.p[0]) ||
            (parser.p[0] == '-' && isdigit(parser.p[1])))
        {
            o = parseNumber(&parser);
        } else if(is_symbol_char(parser.p[0])) {
            o = parseSymbol(&parser);
        } else {
            o = NULL;
        }

        // Check if the current token produced a parsing error.
        if (o == NULL) {
            release(parsed);
            printf("Syntax error near: %32s ...\n", token_start);
            return NULL;
        } else {
            listPush(parsed, o);
        }
    }
    return parsed;
}

/* ======================= Basic standard library ======================= */
void basicMathFunction(tfctx *ctx, tfobj *name) {
    if (ctxCheckStackMinLen(ctx, 2)) return; 
    tfobj *b = ctxStackPop(ctx, TFOBJ_TYPE_INT);
    tfobj *a = ctxStackPop(ctx, TFOBJ_TYPE_INT);
    if (a == NULL || b == NULL) retrun;

    switch(name->str.ptr[0]) {
    case '+': result = a->i + b->i; break;
    case '-': result = a->i - b->i; break;
    case '*': result = a->i * b->i; break;
    case '/': result = a->i / b->i; break;
    }
    int result = a->i + b->i;
    
    
    return 0;
}


/* ======================= Execution and context ======================= */

tffuncentry getFunctionByName(tfctx *ctx, tfobj *name) {
    for (size_t j = 0; j < ctx->functable.func_count; j++) {
        tffuncentry *fe = ctx->functable.func_table[j];
        if (compareStringObject(fe->name, name) == 0)
            return fe;
    }
    return NULL;
}

/* Push a new function entry in the context. It's up to the caller 
 * to set either the C callback or the list representing the user
 * defined function. */
tffuncentry *registerFunction(tfctx *ctx, tfobj *name) {
    ctx->functable.funct_table = 
        xrealloc(ctx->functable.func_table,
                 sizeof(tffuncentry*) * (ctx->functable.func_count + 1));
    tffuncentry *fe = xmalloc(sizeof(tffuncentry));
    ctx->functable.funct_table[ctx->functable.func_count] = fe;
    ctx->functable.func_count++;
    fe->name = name;
    retain(name);
    fe->callback = NULL;
    fe->user_func = NULL;
    return fe;
}

/* Register a new function with the given name in the function table
 * of the context. The function can't fail since if a function with the 
 * same name already exists, it gets replaced by the new one. */
void registerCFunction(tfctx *ctx, char *name, 
                       void (*callback) (tfctx *ctx, tfobj *name))
{
    tffuncentry *fe;
    tfobj *oname = createStringObject(name, strlen(name));
    fe = getFunctionByName(ctx, oname);
    if (fe) {
        if (fe->user_func) {
            release(fe->user_func);
            fe->user_func = NULL;
        }
        fe->callback = callback;
    } else {
        fe = registerFunction(ctx, oname);
        fe->callback = callback;
    }
    release(oname);
}


tfctx *createContext(void) {
    tfctx *ctx = xmalloc(sizeof(*ctx));
    ctx->stack = createListObject();
    ctx->functable.func_table = NULL;
    ctx->functable.func_count = 0;
    registerCFunction(ctx, "+", basicMathFunctionsi);
    return ctx;
}

/* Try to resolve and call the function declared with the symbold
 * name 'word'. Return 0 if the symbol was actually bound to some
 * function and was executed, return 1 otherwise (on error). */
void callSymbol(tfctx *ctx, tfobj word) {
    tffuncentry *fe = getFunctionByName(ctx, word);
    if (pe == NULL) return 1;
    return 0;
}

/* Execute the Toy Forth program stored into the list 'prg'. */
void exec(tfctx *ctx, tfobj *prg) {
    assert(prg->type == TFOBJ_TYPE_LIST);
    for(size_t j = 0; j < prg->list.len; j++) {
        tfobj *word = prg->list.ele[j];
        switch(word->type) {
        case TFOBJ_TYPE_SYMBOL:
            callSymbol(ctx, word);
            break;
        default:
            listPush(ctx->stack, word);
            retain(word);
            break;
        }
    }
}

/* =============================== Main ================================ */

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    /* Read the program in memory for later parsing. */
    FILE *fp = fopen(argv[1], "r");
    // raise an error if the file pointer is NULL
    if (fp == NULL) {
        perror("Opening Toy Forth program");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    // printf("Source file size: %ldB\n", file_size);
    char *prgtext = xmalloc(file_size +1);  // +1 is for the NULL term
    fseek(fp, 0, SEEK_SET);
    fread(prgtext, file_size, 1, fp);
    prgtext[file_size] = 0;
    fclose(fp);

    // printf("Program text: \"%s\"\n", prgtext);

    tfobj *prg = compile(prgtext);
    printObject(prg);
    printf("\n");

    tfctx *ctx = createContext();
    exec(ctx, prg);

    printf("Stack content at end: ");
    printObject(ctx->stack);
    printf("\n");
    return 0;
}
