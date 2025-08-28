# Lesson 15

## Main Topics
1. **From Fractions to Structures**
   * Continuing from the previous lesson on fractions and structures.
   * Introducing a more complex example to better understand how C structures can be used.

2. **Reimplementing the `tac` Command**
   * The goal: replicate the Unix `tac` utility (like `cat` but prints file contents in reverse order).
   * Program requirements: read all lines of a file, store them in memory, and print them backwards.

3. **Program Arguments (`argc`, `argv`)**
   * Explanation of `main(int argc, char **argv)`.
   * Understanding how command-line arguments are passed.
   * What `char **argv` means (an array of strings as pointers to characters).

4. **File Handling in C**
   * Using `FILE *` and `fopen` to open files.
   * Modes of opening (`"r"` for read).
   * Error handling: checking if `fopen` returns `NULL`.
   * Closing files with `fclose`.

5. **Reading Files Line by Line**
   * Using `fgets` to read lines into a buffer.
   * Handling end-of-file and newlines.
   * First implementation similar to `cat`.

6. **Data Structures: Linked Lists**
   * Defining a `struct line` containing:
     * A string (`char *s`).
     * A pointer to the next node (`struct line *next`).
   * Dynamically allocating memory with `malloc`.
   * Copying strings safely into allocated memory (`strlen`, loop copy).
   * Building a **linked list in reverse order** while reading lines.

7. **Traversing and Printing the List**
   * Iterating from the head of the list through `next` pointers.
   * Printing lines in reverse order (achieving the `tac` functionality).

8. **Abstract Thinking with Structures**
   * How linked lists represent an abstraction independent of memory location.
   * Introduction to data structures as models in C (graphs, lists, etc.).
   * Efficiency considerations:

     * Time complexity O(n) for reading and printing.
     * Memory overhead (storing the whole file in memory).

**In summary:** Lesson 15 introduces **command-line arguments**, **file handling**, and especially the concept of **linked lists** in C, by building a simplified reimplementation of the Unix `tac` command.
