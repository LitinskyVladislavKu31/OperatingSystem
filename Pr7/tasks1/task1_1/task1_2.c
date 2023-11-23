#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#define SHM_SIZE 1024  // Розмір сегменту пам'яті

// Структура для зберігання даних
struct SharedData {
    int count;
    int numbers[100];  // Максимальна кількість чисел
};

// Глобальні змінні для вказівника на сегмент пам'яті та м'ютекс
struct SharedData *shared_memory;
pthread_mutex_t *mutex;

// Функція-обробник сигналів
void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        // Отримання доступу до м'ютексу
        pthread_mutex_lock(mutex);

        // Виведення суми в консоль
        printf("Перший процес: Отримано суму від другого процесу: %d\n", shared_memory->numbers[0]);

        // Відправлення сигналу другому процесу
        kill(getpid() + 1, SIGUSR1);

        // Звільнення м'ютексу
        pthread_mutex_unlock(mutex);
    } else if (signo == SIGUSR2) {
        // Закінчення роботи
        shmdt(shared_memory);
        shmctl(shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666), IPC_RMID, NULL);
        pthread_mutex_destroy(mutex);
        exit(0);
    }
}

int main() {
    // Створення м'ютексу
    int fd = shm_open("/myshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
ftruncate(fd, sizeof(pthread_mutex_t));
    mutex = (pthread_mutex_t*)mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    pthread_mutex_init(mutex, NULL);

    // Створення сегменту пам'яті
    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    shared_memory = (struct SharedData *)shmat(shmid, NULL, 0);

    // Встановлення обробників сигналів
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    while (1) {
        // Очікування на введення користувача
        printf("Перший процес: Введіть кількість чисел (або -1 для завершення): ");
        scanf("%d", &(shared_memory->count));

        if (shared_memory->count == -1) {
            // Перший процес відправляє сигнал другому процесу про завершення роботи
            kill(getpid() + 1, SIGUSR2);
            break;
        }

        // Введення чисел користувачем та запис у сегмент пам'яті
        for (int i = 1; i <= shared_memory->count; ++i) {
            printf("Перший процес: Введіть число %d: ", i);
            scanf("%d", &(shared_memory->numbers[i]));
        }

        // Відправлення сигналу другому процесу
        kill(getpid() + 1, SIGUSR1);

        // Очікування відповіді від другого процесу
        pause();
    }

    // Очікування завершення роботи другого процесу
    wait(NULL);

    // Завершення роботи першого процесу
    shmdt(shared_memory);
    pthread_mutex_destroy(mutex);

    return 0;
}
