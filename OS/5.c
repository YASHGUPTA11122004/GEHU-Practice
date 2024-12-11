#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[100];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }
    pid = fork();
    if (pid < 0) 
    {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) 
    {
        // Child process
        close(pipefd[1]);  // Close write end of the pipe
        read(pipefd[0], read_msg, sizeof(read_msg));
        printf("Child Process: Received message: '%s'\n", read_msg);
        close(pipefd[0]);  // Close read end of the pipe
    } 
    else {
        // Parent process
        close(pipefd[0]);  // Close read end of the pipe
        printf("Parent Process: Sending message to child...\n");
        write(pipefd[1], write_msg, strlen(write_msg) + 1);
        close(pipefd[1]);  // Close write end of the pipe
        wait(NULL);        // Wait for child process to finish
    }

    return 0;
}

// Parent Process: Sending message to child...
// Child Process: Received message: 'Hello from parent process!'

