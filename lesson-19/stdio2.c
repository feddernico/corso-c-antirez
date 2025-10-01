#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define HEXDUMP_CHARS_PER_LINE 16
void hexdump(void *p, size_t len) {
    unsigned char *byte = p;
    size_t po = 0;
    for (int j = 0; j < (int) len; j++) {
        // prints a number passed as an int as hex
        printf("%02X ", byte[j]);
        if ((j+1) % HEXDUMP_CHARS_PER_LINE == 0 || j == (int)len-1) {
            if (j == (int)len-1) {
                int pad = HEXDUMP_CHARS_PER_LINE -
                    (len % HEXDUMP_CHARS_PER_LINE);
                pad %= HEXDUMP_CHARS_PER_LINE;
                for (int i = 0; i < pad; i++) printf("~~ ");
            }
            printf("\t");
            for (size_t i = po; (int)i <= j; i++) {
                int c = isprint(byte[i]) ? byte[i] : '.';
                printf("%c", (char)c);
            }
            printf("\n");
            po = j+1;
        }
    }
}

int main(void) {
    int fd = open("stdio2.c", O_RDONLY);
    printf("Error number is %d (ENOENT is: %d)\n", errno, ENOENT);
    // In the POSIX standard system calls return -1 to signal an error
    if (fd == -1) {
        perror("Unable to open file");
        return 1;
    }

    char buf[32];
    ssize_t nread; 
    while (1) {
        nread = read(fd, buf, sizeof(buf));
        if (nread == -1) {
            perror("Error reading file");
            return 0;
        }
        if (nread == 0) break;
        hexdump(buf, nread);
    }

    close(fd);
    return 0;
}
