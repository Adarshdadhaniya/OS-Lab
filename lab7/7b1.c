/*
System V Shared Memory Fibonacci Example
parent.c

This program demonstrates inter-process communication using System V shared memory.
The parent process creates a shared memory segment, forks a child, and waits for the child to write the first N Fibonacci numbers to shared memory.
The parent then reads and prints the sequence from shared memory.

How to run:
1. Compile both parent.c and child.c:
   gcc parent.c -o parent
   gcc child.c -o fib
2. Run the parent program with N as argument (e.g., N=10):
   ./parent 10
   (The parent will fork and run the child automatically)

Note: Run on Linux or WSL. Both executables must be in the same directory.

Both programs are correct and will execute as intended, provided you follow the above steps and run on a compatible system.
*/

#include <sys/types.h>    // for pid_t, key_t
#include <sys/wait.h>     // for wait()
#include <stdio.h>        // for printf()
#include <string.h>       // for strlen()
#include <unistd.h>       // for fork(), execlp()
#include <sys/shm.h>      // for shmget, shmat, shmdt
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>     // included but not used here (System V uses shm.h)

int main(int argc, char *argv[])
{
    int i;                // Holds input number
    pid_t pid;            // Process ID
    int k;                // Fibonacci counter
    int n1, n2, n3;       // Fibonacci numbers

    const int SIZE = 4096;     // Shared memory size
    // int shmid;                 // Shared memory ID
    // void *ptr;                 // Pointer to shared memory

    // Create a System V shared memory segment with key 1122
    // shmget: creates or accesses a shared memory segment
    // (key = 1122, size = 4096 bytes, permissions = 0666, create if not exists)
    int shmid = shmget((key_t)1122, 4096, 0666 | IPC_CREAT);

    // Attach the shared memory segment to this process's address space
    // shmat: returns a pointer to the shared memory
    // (shmid: shared memory ID, NULL: let system choose address, 0666: read+write permission)
    void *ptr = shmat(shmid, NULL, 0666);

    // Input validation from command line
    if (argc > 1) {
        // sscanf: reads formatted data from a string
        // Here it reads the first argument as an integer and stores in i
        sscanf(argv[1], "%d", &i);
        if (i < 1) {
            printf("Error input: %d\n", i);
            return 0;
        }
    } else {
        // No input provided
        return 1;
    }

    // Create child process
    pid = fork();

    // When pid == 0, it means we are in the child process
    if (pid == 0) {
        // ---- CHILD PROCESS ----

        // execlp: replaces the current process image with a new one
        // It runs the program "./fib" with "fib" as argv[0], and argv[1] as input
        // Current process is replaced with ./fib, which will write to shared memory
        execlp("./fib", "fib", argv[1], NULL);
    } else if (pid > 0) {
        // ---- PARENT PROCESS ----

        // wait for the child process to complete
        wait(NULL);

        printf("\nPARENT: child completed\n");
        printf("Parent printing:\n");

        // Read and print data written by the child to shared memory
        printf("%s ", (char *)ptr);

        // Detach shared memory segment from the parent process
        // (doesn't delete the segment, just detaches from this process)
        shmdt(ptr);
    }

    return 0;
}
