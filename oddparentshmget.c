#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Define a structure to hold shared data
typedef struct {
    int n;              // Number of odd numbers to generate
    int arr[100];       // Array to hold the odd numbers
} pack_t;

int main() {
    key_t key = 1234; // Unique key for shared memory segment

    // Create shared memory segment
    int shmid = shmget(key, sizeof(pack_t), 0666 | IPC_CREAT);

    // Attach shared memory segment to parent process
    pack_t* shm_ptr = (pack_t*) shmat(shmid, NULL, 0666);

    printf("[PARENT] Created shared memory with key = %d, id = %d, address = %p\n", key, shmid, shm_ptr);

    // Take input from user for how many odd numbers to generate
    printf("[PARENT] Enter n: ");
    scanf("%d", &shm_ptr->n);

    pid_t child_pid;

    // Create child process
    if ((child_pid = fork()) == 0) {
        // In child process: replace with child program
        execlp("./child", "child", NULL);
    } else {
        // In parent process: wait for child to finish
        wait(NULL);

        printf("[PARENT] Child finished executing.\n");
        printf("[PARENT] The first %d odd numbers are:\n", shm_ptr->n);

        // Print the odd numbers written by child
        for (int i = 0; i < shm_ptr->n; i++)
            printf("%d ", shm_ptr->arr[i]);

    }

    // Detach from shared memory
    shmdt((void*) shm_ptr);

    // Mark the shared memory for deletion
    shmctl(shmid, IPC_RMID, NULL);

    printf("[PARENT] Shared Memory Deleted\n");

    return 0;
}

