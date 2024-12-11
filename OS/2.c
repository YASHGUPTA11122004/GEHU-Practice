#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // For wait()

int main() {
    int start, end;
    printf("Enter the range (start and end): ");
    scanf("%d %d", &start, &end);

    pid_t pid = fork();

    if (pid < 0) {
        // Error occurred
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process: Computes the sum of odd numbers
        int odd_sum = 0;
        for (int i = start; i <= end; i++) {
            if (i % 2 != 0) {
                odd_sum += i;
            }
        }
        printf("Child Process: Sum of odd numbers from %d to %d is %d\n", start, end, odd_sum);
    } else {
        // Parent process: Computes the sum of even numbers
        int even_sum = 0;
        for (int i = start; i <= end; i++) {
            if (i % 2 == 0) {
                even_sum += i;
            }
        }

        // Wait for child process to complete
        wait(NULL);

        printf("Parent Process: Sum of even numbers from %d to %d is %d\n", start, end, even_sum);
    }

    return 0;
}


// Enter the range (start and end): 1 10
// Child Process: Sum of odd numbers from 1 to 10 is 25
// Parent Process: Sum of even numbers from 1 to 10 is 30
