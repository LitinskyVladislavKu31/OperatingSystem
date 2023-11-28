#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

int *data;

void reader_handle_signal(int sig) {
    if (sig == SIGUSR2) {
        // Print the sum received from the reader process
        printf(" Process 2: Received sum: %d\n", data[0]);

        // Detach shared memory segment
        if (shmdt(data) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int buffer_size = atoi(argv[1]);

    // Create shared memory segment
    key_t key = ftok(".", 's');
    int shmid = shmget(key, (buffer_size + 1) * sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory segment
    data = (int *)shmat(shmid, NULL, 0);
    if (data == (int *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Set the buffer size
    data[0] = buffer_size;

    // Set up the signal handler
    signal(SIGUSR2, reader_handle_signal);

    // Wait for the reader process to finish
    pause();

    return 0;
}
