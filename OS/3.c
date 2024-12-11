#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child Process: Executing...");
        printf(" (PID: %d, Parent PID: %d)\n", getpid(), getppid());
    } else {
        printf("Parent Process: Waiting for child process to complete...\n");

        wait(NULL);

        printf("Parent Process: Child process completed.\n");
        printf("Parent Process: Continuing execution (PID: %d)\n", getpid());
    }

    return 0;
}



// Parent Process: Waiting for child process to complete...
// Child Process: Executing... (PID: 12345, Parent PID: 12344)
// Parent Process: Child process completed.
// Parent Process: Continuing execution (PID: 12344)
