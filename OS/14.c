#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0) {
        // Child process executes the 'ls' command
        execl("/bin/ls", "ls", (char *)NULL);
        printf("execl() failed\n");  // If execl() fails, this line will execute
    } else {
        // Parent process executes the 'date' command
        wait(NULL);
        execl("/bin/date", "date", (char *)NULL);
        printf("execl() failed\n");  // If execl() fails, this line will execute
    }

    return 0;
}


// ls
// file1.txt
// file2.txt
// file3.txt
// ...
// date
// Tue Dec 11 10:22:15 UTC 2024
