/* Program to demonstrate the creation of an orphan process. */
// ---- orphan.c ---- //

#include <sys/types.h>  // For pid_t: data type used for process IDs
#include <unistd.h>     // For fork(), getpid(), getppid(), sleep()
#include <stdio.h>      // For printf()
#include <stdlib.h>     // For exit()

int main() {
    // pid_t is a data type used to store process IDs
    pid_t child_pid, my_pid, parent_pid;

    // Create a new child process
    child_pid = fork();

    // fork() returns:
    // - 0 to the child process
    // - >0 (child's PID) to the parent process
    // - <0 if fork fails
    if (child_pid < 0) {
        printf("Fork failed. Exiting!\n");
        exit(0);
    }

    // -------------------- CHILD PROCESS --------------------
    if (child_pid == 0) {
        // Even though this block is written first,
        // whether parent or child runs first is decided by the OS scheduler.

        printf("[CHILD] This is the child process.\n");

        my_pid = getpid();      // getpid() returns current process's ID
        parent_pid = getppid(); // getppid() returns parent process's ID

        printf("[CHILD] My pid is %d\n", my_pid);
        printf("[CHILD] My parent's pid is %d\n", parent_pid);

        printf("[CHILD] Sleeping for 10 seconds.\n");
        sleep(10); // Sleep long enough for parent to exit

        // After sleeping, the parent has exited, so this child is now orphaned
        // It is adopted by the 'init' process (PID 1) in Linux/Unix
        printf("[CHILD] My parent ended. So I am an orphan process adopted by init process.\n");
    }

    // -------------------- PARENT PROCESS --------------------
    else {
        printf("[PARENT] This is the parent process.\n");

        my_pid = getpid();       // Parent's own PID
        parent_pid = getppid();  // Parent's parent PID (usually shell)

        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);

        printf("[PARENT] Exiting.\n");
        exit(0); // Parent exits immediately, orphaning the child
    }

    return 0;
}



/*
======================== EXPLANATION ========================

What is pid_t?
- pid_t is a data type used to represent process IDs.

What are getpid() and getppid()?
- getpid() returns the process ID of the current process.
- getppid() returns the process ID of the parent process.

Why does the parent process usually run first?
- Although the child process block is written first,
  the OS scheduler decides which one gets CPU time first.
- Usually, the parent runs first as it already exists in memory,
  while the child is a new process being scheduled.

What is an Orphan Process?
- An orphan process is a child process whose parent has exited.
- In Unix/Linux, such orphan processes are automatically adopted
  by the special process with PID 1 (called `init` or `systemd`).

How does this program demonstrate an orphan?
1. The parent process calls fork() and exits immediately.
2. The child process sleeps for 10 seconds.
3. During that sleep, the parent finishes and exits.
4. The child wakes up and sees that its parent has changed
   (typically to PID 1), meaning it's now an orphan.

How to observe it:
1. Run this program on Linux.
2. While it's sleeping, open another terminal and run:
   ps -ef | grep orphan
3. After parent exits, check child’s PPID — it will be 1.

=============================================================
*/
