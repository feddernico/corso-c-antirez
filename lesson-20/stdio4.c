#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void) {
    int fd = open("stdio3.c", O_RDONLY);
    /* the file descriptor is 3 because:
     * 0 - standard input
     * 1 - standard output
     * 2 - standard error */
    printf("Open file descriptor: %d\n", fd);
    void *mem = mmap(NULL, 100, PROT_READ, MAP_FILE|MAP_SHARED, fd, 0);
    printf("File mapped at  %p\n", mem);
    char *s = mem;
    for (int j = 0; j < 10; j++) {
        printf("s[%d] = %c\n", j, s[j]);
    }
    return 0;
}
