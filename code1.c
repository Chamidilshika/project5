#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SIZE 1024

int main() {
    key_t key = IPC_PRIVATE; // Unique key for shared memory segment
    int shmid, pid;

    // Create shared memory segment
    if ((shmid = shmget(key, SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory segment to parent process
    char *data = shmat(shmid, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Create child process
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    // Parent process
    if (pid > 0) {
        printf("Parent writing to shared memory...\n");
        sprintf(data, "Hello from parent!");
        printf("Parent wrote: %s\n", data);

        // Wait for child process to finish
        wait(NULL);

        // Detach shared memory segment from parent process
        if (shmdt(data) < 0) {
            perror("shmdt");
            exit(1);
        }

        // Deallocate shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) < 0) {
            perror("shmctl");
            exit(1);
        }
    }

    // Child process
    else {
        printf("Child reading from shared memory...\n");
        printf("Child read: %s\n", data);

        // Detach shared memory segment from child process
        if (shmdt(data) < 0) {
            perror("shmdt");
            exit(1);
        }
    }

    return 0;
}

