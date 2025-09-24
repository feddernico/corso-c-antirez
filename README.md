# Corso di programmazione in C
**by Salvatore Sanfilippo aka Antirez**

🇮🇹: Gli script del Corso C, creato da Antirez e [disponibile su YouTube](https://www.youtube.com/watch?v=HjXBXBgfKyk&amp;list=PLrEMgOSrS_3cFJpM2gdw8EGFyRBZOyAKY)

## Lesson 1: Overview
- intro to the course
- overview of C language
- first program "Hello World"
- compilation process
- preprocessor and headers
- function prototypes

## Lesson 7: Overview
- tail call optimisation
- while loop
- for loop
- for loop without initialisation, stop condition, and increment
- switch
- declaring variables inside the switch by using a block

## Lesson 15: Overview
- program arguments (`argc`, `argv`)
- opening and closing files with `fopen` and `fclose`
- reading files line by line using `fgets`
- defining a linked list with `struct`
- dynamically allocating memory with `malloc`
- copying strings into allocated memory
- inserting nodes at the head to reverse order
- traversing and printing a linked list
- reimplementing the Unix `tac` command
- complexity: O(n) build, O(n) print, memory trade-offs

## Lesson 16: Overview
- motivation for prefixed length strings
- struct layout with natural alignment
- flexible array member (`char str[]`, C99)
- creating a PLS with `ps_create` using `malloc`
- returning `p->str` and recovering header with pointer arithmetic
- reference counting (`ps_retain`, `ps_release`)
- freeing safely with `ps_free`
- validating objects with a `magic` field (`0xDEADBEEF`)
- utility functions: `ps_print`, `ps_len`, `ps_validate`
- safer memory management vs raw `malloc`/`free`
- trade-offs: extra memory overhead, optional debug builds
