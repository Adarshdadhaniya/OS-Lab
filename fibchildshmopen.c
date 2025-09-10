/*
prime shmopen mmap - child.c

This program finds all prime numbers in a given range and writes them to POSIX shared memory using mmap.
The parent process (parent.c) reads and prints the sequence from shared memory after the child completes.

How to run:
1. Compile both parent.c and child.c (add -lrt for POSIX shared memory):
   cc parent.c -o parent -lrt
   cc child.c -o child -lrt
2. Run the parent program with two arguments (lower and upper bounds, e.g., 10 and 50):
   ./parent 10 50
   (The parent will fork and run the child automatically)

Note: Run on Linux or WSL. Both executables must be in the same directory.

Both programs are correct and will execute as intended, provided you follow the above steps and run on a compatible system.
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    void *ptr;  // Pointer to shared memory
    const int SIZE = 4096;

    // Create or open a shared memory object with read/write permissions
    int shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);

    // Set size of shared memory
    ftruncate(shm_fd, SIZE);

    // Map shared memory object in the process’s address space
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("CHILD:\n");

    // Convert command line arguments to integers
    int i = atoi(argv[1]);  // Lower bound
    int j = atoi(argv[2]);  // Upper bound
    int flag = 0;           // Flag to check if number is prime

    printf("The prime numbers in the range %d and %d are:\n", i, j);

    // Loop over numbers in the range [i, j)
    for (int num = i; num < j; num++) {
        flag = 0;

        // Check divisibility from 2 to num/2
        for (int k = 2; k <= num / 2; k++) {
            if (num % k == 0) {
                flag = 1;   // Not a prime
                break;
            }
        }

        // If flag is still 0, number is prime
        if (flag == 0 && num > 1) {
            printf("%d\t", num);                        // Print to console
            sprintf(ptr, "%d\t", num);
            ptr+=strlen(ptr);   // Append to shared memory
        }
    }

    printf("\n");

    return 0;
}









// child.c
//
// This program generates the first N Fibonacci numbers and writes them to POSIX shared memory using mmap.
// The parent process (parent.c) reads and prints the sequence from shared memory after the child completes.
//
// How to run:
// 1. Compile both parent.c and child.c (add -lrt for POSIX shared memory):
//    cc parent.c -o parent -lrt
//    cc child.c -o fib -lrt
// 2. Run the parent program with N as argument (e.g., N=10):
//    ./parent 10
//    (The parent will fork and run the child automatically)
//
// Note: Run on Linux or WSL. Both executables must be in the same directory.

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int k = 2, n1, n2, n3;

    void *ptr;                         // Pointer to shared memory
    int shm_fd;                        // File descriptor for shared memory

    // Create or open a shared memory object named "VSS" with read-write permission
    shm_fd = shm_open("VSS", O_CREAT | O_RDWR, 0666);

    // Set the size of the shared memory object
    ftruncate(shm_fd, 4096);

    // Map the shared memory into the address space of this process
    ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("CHILD:\n");

    // Read the value of N from command-line argument
    int n = atoi(argv[1]);

    // Initialize first two Fibonacci numbers
    n1 = 0;
    n2 = 1;

    // Write the first two numbers into shared memory using sprintf
    sprintf(ptr, "%d ", n1);
    ptr += strlen(ptr); // Move pointer forward to the next write location

    sprintf(ptr, "%d ", n2);
    ptr += strlen(ptr);

    // Print the first two numbers
    printf("%d %d ", n1, n2);

    // Generate the remaining Fibonacci numbers
    while (k < n)
    {
        n3 = n1 + n2;

        // Write the number to shared memory
        sprintf(ptr, "%d ", n3);
        ptr += strlen(ptr);  // Move pointer forward

        // Print the number to screen
        printf("%d ", n3);

        // Prepare for next iteration
        n1 = n2;
        n2 = n3;
        k++;
    }
}