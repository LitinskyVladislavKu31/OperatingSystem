#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Розмір сегменту пам'яті

// Глобальна змінна для вказівника на сегмент пам'яті
int *shared_memory;

// Функція-обробник сигналів
void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        // Обчислення суми та запис у спільний сегмент пам'яті
        int sum = 0;
        int count = shared_memory[0];  // Перший елемент масиву - кількість чисел

        for (int i = 1; i <= count; ++i) {
            sum += shared_memory[i];
        }

        shared_memory[0] = sum;  // Запис суми на перше місце
    } else if (signo == SIGUSR2) {
        // Сигнал про завершення роботи другого процесу
        shmdt(shared_memory);  // Від'єднання сегменту пам'яті
        shmctl(shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666), IPC_RMID, NULL);  // Видалення сегменту пам'яті
        exit(0);
    }
}

int main() {
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

        // Перший процес відправляє сигнал другому процесу
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

