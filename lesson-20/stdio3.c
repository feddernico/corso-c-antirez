#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    /* you are expecting to see "Hello World" first and then the sleep.
     * This is is not the case actually, because libc implements 
     * the buffering abstraction. */
    //printf("Hello World");
    
    // we can rewrite the printf this way:
    char *mystr = "Hello World";
    size_t len = strlen(mystr);
    for (size_t j = 0; j < len; j++) { 
        // to write n characters, I use n system calls, which is slow...
        //write(STDOUT_FILENO, mystr+j, 1);
        
        /* libc instead of calling write for every char written,
         * it uses a buffer, allocates a bit of memory using malloc,
         * and everytime that I write, nothing is written on the file,
         * whenever the buffer is full or there is a newline,
         * the buffer gets emptied into the file. */
        putchar(mystr[j]);
        // there is a way a library call to trigger this behaviour.
        fflush(stdout);
        usleep(100000);
    }

    // why the system can actually sleep?
    // beacause the system uses pre-emptive multitasking.
    sleep(5);
    return 0;
}
