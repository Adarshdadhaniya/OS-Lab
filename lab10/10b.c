

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <signal.h>

int main(int argumentCount, char *argumentVector[]) {
    int i, k1, k2, sharedMemoryFileDescriptor;
    const int SIZE = 4096;
    pid_t processID;
    void *ptr;

    if (argumentCount > 2) {
        sscanf(argumentVector[1], "%d", &k1);
        sscanf(argumentVector[2], "%d", &k2);

        if (k1 < k2)
            printf("Error input %d\n", k1);

        return (0);
    } else {
        printf("Error: Minimum of two arguments must be passed as command line arguments\n");
        exit(0);
    }

    processID = fork();
    if (processID == 0) {
        execlp("/bin/sh", "sh", argumentVector[1], argumentVector[2], NULL);
    } else if (processID > 0) {
        wait(NULL);
        printf("Parent child complete\n");
        sharedMemoryFileDescriptor = shm_open("VSS", O_RDONLY, 0660);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, sharedMemoryFileDescriptor, 0);
        printf("%s\n", (char *)ptr);
        shm_unlink("VSS");
    }

    return (0);
}