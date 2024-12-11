#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execlp("ls", "ls", (char *)NULL);
        perror("execlp failed");
        return 1;
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp failed");
        return 1;
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}


