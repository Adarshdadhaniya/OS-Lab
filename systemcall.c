#include <sys/types.h>  // For types like off_t
#include <sys/stat.h>   // For open() mode constants
#include <fcntl.h>      // For open() flags like O_RDWR
#include <unistd.h>     // For read(), write(), lseek(), close()
#include <stdio.h>      // For printf()
#include <stdlib.h>     // For exit()

#define BUFFER_SIZE 30

int main() {
    int fd = open("myfile.txt", O_RDWR);  // Open file in read-write mode
    int n;
    char buffer[BUFFER_SIZE];

    printf("File descriptor is %d\n", fd);

    // Check if file was opened successfully
    if (fd == -1) {
        printf("Failed to open file.\n");
        exit(0);
    }

    // ------------------ READ FIRST 10 CHARACTERS ------------------
    printf("Reading first 10 characters from file: \n");
    n = read(fd, buffer, 10);  // Read 10 characters from start
    write(1, buffer, n);       // Write to stdout (fd 1)

    // ------------------ SKIP 5 CHARACTERS AHEAD ------------------
    printf("\nSkipping 5 characters from current position in the file: \n");
    lseek(fd, 5, SEEK_CUR);    // Skip 5 characters ahead from current position
    n = read(fd, buffer, 10);  // Read next 10 characters
    write(1, buffer, n);

    // ------------------ GO 10 CHARACTERS BACK ------------------
    printf("\nGoing 10 characters before the current position in the file: \n");
    lseek(fd, -10, SEEK_CUR);  // Go 10 characters back
    n = read(fd, buffer, 10);  // Read 10 characters again
    write(1, buffer, n);

    // ------------------ SEEK FROM END ------------------
    printf("\nGoing to 5th last character in the file: \n");
    lseek(fd, -5, SEEK_END);   // Go 5 characters before end of file
    n = read(fd, buffer, 5);   // Read last 5 characters
    write(1, buffer, n);

    // ------------------ SEEK ABSOLUTE POSITION ------------------
    printf("\nGoing to the 3rd character in the file: \n");
    lseek(fd, 3, SEEK_SET);    // Go to 3rd character from start
    n = read(fd, buffer, 5);   // Read 5 characters from there
    write(1, buffer, n);

    return 0;
}


/*
======================= EXPLANATION =======================

What does this program do?
- Demonstrates how to use low-level file system syscalls:
  `open()`, `read()`, `write()`, and `lseek()`.

What is a file descriptor?
- A file descriptor is an integer returned by `open()`.
- It is used to refer to the opened file in subsequent calls.

What is happening step-by-step?

1. open("myfile.txt", O_RDWR)
   - Opens the file in read/write mode.
   - Returns a file descriptor (fd).

2. read(fd, buffer, 10)
   - Reads first 10 bytes from the file into buffer.

3. write(1, buffer, n)
   - Writes the contents of the buffer to `stdout` (fd = 1).

4. lseek(fd, 5, SEEK_CUR)
   - Moves the file pointer 5 bytes forward from current position.

5. lseek(fd, -10, SEEK_CUR)
   - Moves the file pointer 10 bytes back from current position.

6. lseek(fd, -5, SEEK_END)
   - Moves to the 5th last byte of the file.

7. lseek(fd, 3, SEEK_SET)
   - Moves the pointer to 3rd byte from beginning of file.

What are SEEK_SET, SEEK_CUR, SEEK_END?
- SEEK_SET: from beginning of file
- SEEK_CUR: from current position
- SEEK_END: from end of file

What is BUFFER_SIZE?
- Just a fixed-size array to hold characters read from file.
- Not all 30 bytes are used each time; only the needed part is filled.

What is the content of myfile.txt?
- A sample file:
  "this is my file. it has characters. we use open syscall to get the file descriptor, and use read, write and lseek to jump across the file."

===========================================================
*/
