#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        sleep(5);  // Delay to ensure parent process terminates first
        printf("Child Process: I am now an orphan, adopted by init/systemd (PID: %d)\n", getppid());
    } else {
        printf("Parent Process: I am exiting, leaving my child process an orphan.\n");
    }

    return 0;
}

// Parent Process: I am exiting, leaving my child process an orphan.
// Child Process: I am now an orphan, adopted by init/systemd (PID: 1)

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child Process: Exiting...\n");
    } else {
        sleep(10);  // Delay to keep the parent alive while the child becomes a zombie
        printf("Parent Process: Checking child status, child might be a zombie now.\n");
    }

    return 0;
}

// Child Process: Exiting...
// Parent Process: Checking child status, child might be a zombie now.
