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
#include <semaphore.h>

#define SHM_SIZE 1024  // Розмір сегменту пам'яті

// Структура для зберігання даних
struct SharedData {
    int count;
    int numbers[100];  // Максимальна кількість чисел
};

// Глобальні змінні для вказівника на сегмент пам'яті, м'ютекс та семафори
struct SharedData *shared_memory;
pthread_mutex_t *mutex;
sem_t *server_sem, *client_sem;

// Функція-обробник сигналів
void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        // Отримання доступу до м'ютексу
        pthread_mutex_lock(mutex);

        // Очікування, коли другий процес завершить обчислення суми
        sem_wait(client_sem);

        // Виведення суми в консоль
        printf("Перший процес: Отримано суму від другого процесу: %d\n", shared_memory->numbers[0]);

        // Відправлення сигналу другому процесу
        sem_post(server_sem);

        // Звільнення м'ютексу
        pthread_mutex_unlock(mutex);
    } else if (signo == SIGUSR2) {
        // Закінчення роботи
        shmdt(shared_memory);
        shmctl(shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666), IPC_RMID, NULL);
        pthread_mutex_destroy(mutex);

        // Закриття та знищення семафорів
        sem_close(server_sem);
        sem_close(client_sem);
        sem_unlink("/my_server_sem");
        sem_unlink("/my_client_sem");

        exit(0);
    }
}

int main() {
    // Створення м'ютексу
    int fd = shm_open("/myshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, sizeof(pthread_mutex_t));
    mutex = (pthread_mutex_t*)mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    pthread_mutex_init(mutex, NULL);

    // Створення сегменту пам'яті
    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    shared_memory = (struct SharedData *)shmat(shmid, NULL, 0);

    // Створення семафорів
    server_sem = sem_open("/my_server_sem", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    client_sem = sem_open("/my_client_sem", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);

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

        // Встановлення семафора для синхронізації
        sem_post(server_sem);

        // Очікування відповіді від другого процесу
        sem_wait(client_sem);
    }

    // Очікування завершення роботи другого процесу
    wait(NULL);

    // Завершення роботи першого процесу
    shmdt(shared_memory);
    pthread_mutex_destroy(mutex);

    // Закриття та знищення семафорів
    sem_close(server_sem);
    sem_close(client_sem);
    sem_unlink("/my_server_sem");
    sem_unlink("/my_client_sem");

    return 0;
}
