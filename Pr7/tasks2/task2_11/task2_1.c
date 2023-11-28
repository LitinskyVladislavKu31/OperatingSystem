#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
int main(){
    int shmid;
    key_t key;
    int *shared_memory;
    int n, i;
    sem_t *semaphore;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    key = ftok("shmfile", 65);
    shmid = shmget(key, n * sizeof(int), IPC_CREAT | 0666);
    printf("ID shared memory: %d\n", shmid);
    shared_memory = (int *)shmat(shmid, NULL, 0);
    printf("Enter the values of the elements:\n");
    for(i = 0; i < n; i++){
        scanf("%d", &shared_memory[i]);
    }
    sem_unlink("/my_semaphore");
    semaphore = sem_open("/my_semaphore", O_CREAT | O_EXCL, 0666, 0);
    if(semaphore == SEM_FAILED){
        perror("Semaphore creation/opening failed");
        return -1;
    }
    sem_post(semaphore);
    shmdt((void *)shared_memory);
    sem_close(semaphore);
    return 0;
}