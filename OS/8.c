#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT);
    char *str = (char*) shmat(shmid, NULL, 0);

    printf("Write Data to Shared Memory: ");
    fgets(str, SHM_SIZE, stdin);

    printf("Data written to shared memory: %s\n", str);

    printf("Press any key to detach and exit.\n");
    getchar();

    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

// Output
// Write Data to Shared Memory: Hello from process 1!
// Data written to shared memory: Hello from process 1!
// Press any key to detach and exit.
