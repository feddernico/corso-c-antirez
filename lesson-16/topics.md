# Lesson 16

## Main Topics
1. **Motivation for Prefixed Length Strings**
   * Limitations of traditional C strings (`\0`-terminated).
   * Idea of storing the length explicitly before the string.
   * Advantages: binary safety (can contain `\0` inside), O(1) length lookup.

2. **Struct Layout and Memory Alignment**
   * Defining a `struct pls` with fields:
     * `uint32_t len` (length of the string).
     * `uint32_t refcount` (reference count).
     * `uint32_t magic` (validation guard).
     * `char str[]` (flexible array member).
   * Natural alignment of fields (offsets 0, 4, 8).
   * `char str[]` as a C99 flexible array member.

3. **Creating a PLS (`ps_create`)**
   * Using `malloc(sizeof(struct pls) + len + 1)`.
   * Initializing `len`, `refcount`, and `magic` (set to `0xDEADBEEF`).
   * Copying the input string into `p->str` and null-terminating.

4. **Accessing the String**
   * Returning `p->str` so users can interact like a normal C string.
   * Recovering the struct header from the string pointer with pointer arithmetic:
     `struct pls *p = (struct pls *)(s - sizeof(*p));`.

5. **Reference Counting**
   * `ps_retain` increases `refcount` when another ownership is created.
   * `ps_release` decreases `refcount` and frees memory when it reaches zero.
   * Ensuring correct ownership management across multiple variables.

6. **Validation and Safety with Magic**
   * Adding a `magic` field to detect invalid or freed strings.
   * `ps_validate` checks `p->magic == 0xDEADBEEF` before use.
   * Setting `magic = 0` when freeing to invalidate the object.

7. **Other Utility Functions**
   * `ps_print`: prints the string contents using `len`.
   * `ps_len`: returns the length of the string in O(1).
   * `ps_free`: low-level free called by `ps_release`.

8. **Practical Example**
   * Creating a PLS string and assigning it to both a local and global variable.
   * Correct use of `ps_retain` and `ps_release` to manage ownership.
   * Demonstration of double-release errors and how `magic` prevents misuse.

9. **Trade-offs and Debugging**
   * Extra memory overhead for `len`, `refcount`, and `magic`.
   * Safer than raw `malloc`/`free` due to reference counting and validation.
   * Possibility of conditional builds with `#ifdef PLS_DEBUG` to enable/disable `magic`.

**In summary:** This lesson introduces **Prefixed Length Strings** in C using a struct-based design. It covers **memory alignment, flexible array members, reference counting, and safety checks** with a `magic` field, offering a safer and more structured alternative to raw C strings.

