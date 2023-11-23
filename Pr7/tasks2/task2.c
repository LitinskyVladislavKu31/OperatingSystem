#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Розмір сегменту пам'яті
#define SEM_KEY 1234    // Ключ для семафорів

// Глобальні змінні для вказівника на сегмент пам'яті та ідентифікаторів семафорів
int *shared_memory;
int sem_id;

// Структура для ініціалізації семафорів
union semun {
    int val;
    struct semid_ds *buf;
   unsigned short *array;
};

// Функція-обробник сигналів
void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        // Отримання доступу до семафора
        struct sembuf semaphore = {0, -1, 0};  // Зменшення значення семафора на 1

        // Заблокування доступу до ресурсу (очікування семафора)
        semop(sem_id, &semaphore, 1);

        // Обчислення суми та запис у спільний сегмент пам'яті
        int sum = 0;
        int count = shared_memory[0];  // Перший елемент масиву - кількість чисел

        for (int i = 1; i <= count; ++i) {
            sum += shared_memory[i];
        }

        shared_memory[0] = sum;  // Запис суми на перше місце

        // Звільнення семафора
        semaphore.sem_op = 1;  // Збільшення значення семафора на 1
        semop(sem_id, &semaphore, 1);
    } else if (signo == SIGUSR2) {
        // Сигнал про завершення роботи другого процесу
        // Видалення сегменту пам'яті та семафорів
        shmdt(shared_memory);
        shmctl(shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666), IPC_RMID, NULL);
        semctl(sem_id, 0, IPC_RMID);
        exit(0);
    }
}

int main() {
    // Створення семафора
    sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Ініціалізація семафора
    union semun init_sem;
    init_sem.val = 1;  // Початкове значення семафора
    if (semctl(sem_id, 0, SETVAL, init_sem) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Створення сегменту пам'яті
    key_t key = ftok("/tmp", 'S');
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    shared_memory = (int *)shmat(shmid, NULL, 0);

    // Встановлення обробників сигналів
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    while (1) {
        // Введення кількості чисел в користувача
        int count;
        printf("Введіть кількість чисел (або -1 для завершення): ");
        scanf("%d", &count);

        if (count == -1) {
            // Перший процес відправляє сигнал другому процесу про завершення роботи
            kill(getpid() + 1, SIGUSR2);
            break;
        }

        // Запис кількості чисел у спільний сегмент пам'яті
        shared_memory[0] = count;

        // Введення чисел в користувача та запис у спільний сегмент пам'яті
        for (int i = 1; i <= count; ++i) {
            printf("Введіть число %d: ", i);
            scanf("%d", &shared_memory[i]);
        }

        // Відправлення сигналу другому процесу
        kill(getpid() + 1, SIGUSR1);

        // Перший процес чекає відповіді від другого процесу
        pause();

        // Виведення суми, отриманої від другого процесу
        printf("Отримано суму від другого процесу: %d\n", shared_memory[0]);
    }

    // Очікування завершення роботи другого процесу
    wait(NULL);

    // Від'єднання сегменту пам'яті та завершення першого процесу
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
